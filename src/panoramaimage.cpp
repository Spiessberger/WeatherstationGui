#include "panoramaimage.h"

#include <QSGImageNode>
#include <QSGNode>
#include <QSGSimpleTextureNode>

namespace wsgui
{

class PanoramaImageNode : public QSGNode
{
public:
  PanoramaImageNode(PanoramaImage* panoramaImage)
      : m_panoramaImage(panoramaImage)
  {
    QQuickWindow* window = panoramaImage->window();
    const std::vector<QImage>& images = panoramaImage->images();

    m_textures.reserve(images.size());
    for (const QImage& image: images)
    {
      if (image.width() > 0 && image.height() > 0)
      {
        TextureInfo imageTexure;
        imageTexure.texture.reset(window->createTextureFromImage(image));
        imageTexure.sourceSize = image.size();
        m_textures.push_back(std::move(imageTexure));
      }
    }
    scaleToHeight();
  }

  void scaleToHeight()
  {
    const qreal height = m_panoramaImage->height();

    for (TextureInfo& textureInfo: m_textures)
    {
      const qreal width = textureInfo.sourceSize.width() * height / textureInfo.sourceSize.height();
      textureInfo.scaledWidth = width;
    }
  }

  void setOffset(qreal xOffset)
  {
    if (m_textures.empty())
    {
      return;
    }

    qreal x = -xOffset;
    size_t textureIndex = 0;
    while (x + m_textures[textureIndex].scaledWidth < 0)
    {
      x += m_textures[textureIndex].scaledWidth;
      textureIndex = (textureIndex + 1) % m_textures.size();
    }

    const qreal height = m_panoramaImage->height();
    QQuickWindow* window = m_panoramaImage->window();
    size_t nodeIndex = 0;
    while (x < m_panoramaImage->width())
    {
      QSGImageNode* imageNode;
      if (nodeIndex < m_nodes.size())
      {
        imageNode = m_nodes[nodeIndex].get();
      }
      else
      {
        imageNode = window->createImageNode();
        imageNode->setFlag(QSGNode::OwnedByParent, false);
        m_nodes.emplace_back(imageNode);
        appendChildNode(imageNode);
      }

      const TextureInfo& t = m_textures[textureIndex];
      // TODO: check if setting texture every time impacts performance
      imageNode->setTexture(t.texture.get());
      imageNode->setRect(x, 0, t.scaledWidth, height);

      x += t.scaledWidth;
      textureIndex = (textureIndex + 1) % m_textures.size();
      ++nodeIndex;
    }

    for (size_t i = nodeIndex; i < m_nodes.size(); ++i)
    {
      removeChildNode(m_nodes[i].get());
    }
    m_nodes.erase(m_nodes.begin() + nodeIndex, m_nodes.end());
  }

private:
  struct TextureInfo
  {
    std::unique_ptr<QSGTexture> texture = nullptr;
    QSize sourceSize;
    qreal scaledWidth;
  };
  struct ImageNodeInfo
  {
    QSGImageNode* imageNode = nullptr;
    size_t index = 0;
  };
  PanoramaImage* m_panoramaImage;
  std::vector<TextureInfo> m_textures;
  std::vector<std::unique_ptr<QSGImageNode>> m_nodes;
};

PanoramaImage::PanoramaImage(QQuickItem* parent)
    : QQuickItem(parent)
{
  setFlag(QQuickItem::ItemHasContents);
}

const std::vector<QImage>& PanoramaImage::images() const
{
  return m_images;
}

void PanoramaImage::setImages(const std::vector<QImage>& newImages)
{
  if (m_images == newImages)
  {
    return;
  }
  m_images = newImages;
  emit imagesChanged();

  m_updateImageNode = true;
  if (isComponentComplete())
  {
    update();
  }

  if (m_images.empty())
  {
    setSourceSize(QSizeF{});
    return;
  }

  qreal width = 0;
  qreal height = m_images.front().height();
  for (const QImage& image: m_images)
  {
    width += image.width() * height / image.height();
  }
  setSourceSize(QSizeF{width, height});
}

qreal PanoramaImage::xOffset() const
{
  return m_xOffset;
}

void PanoramaImage::setXOffset(qreal newXOffset)
{
  if (qFuzzyCompare(m_xOffset, newXOffset))
  {
    return;
  }
  m_xOffset = newXOffset;
  emit xOffsetChanged();

  if (isComponentComplete())
  {
    update();
  }
}

QSizeF PanoramaImage::sourceSize() const
{
  return m_sourceSize;
}

void PanoramaImage::setSourceSize(const QSizeF& newSourceSize)
{
  if (m_sourceSize == newSourceSize)
  {
    return;
  }
  m_sourceSize = newSourceSize;
  emit sourceSizeChanged();
}

void PanoramaImage::componentComplete()
{
  QQuickItem::componentComplete();

  if (m_images.size() > 0)
  {
    update();
  }
}

QSGNode* PanoramaImage::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
  if (m_updateImageNode || m_images.empty())
  {
    delete oldNode;
    oldNode = nullptr;
    m_updateImageNode = false;
  }

  if (m_images.empty())
  {
    return nullptr;
  }

  auto node = static_cast<PanoramaImageNode*>(oldNode);
  if (node == nullptr)
  {
    node = new PanoramaImageNode(this);
  }
  if (m_updateImageNodeScaling)
  {
    node->scaleToHeight();
    m_updateImageNodeScaling = false;
  }

  node->setOffset(m_xOffset);

  return node;
}

void PanoramaImage::geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry)
{
  m_updateImageNodeScaling = true;
  QQuickItem::geometryChange(newGeometry, oldGeometry);
}

} // namespace wsgui
