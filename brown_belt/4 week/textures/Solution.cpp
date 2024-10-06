#include "Common.h"
#include "Textures.h"
#include <iostream>

using namespace std;


Point CalculateEllipseCenter(Point topLeft, Point bottomRight) {
    Point center;
    center.x = (topLeft.x + bottomRight.x) / 2;
    center.y = (topLeft.y + bottomRight.y) / 2;
    return center;
}

Size GetImageSize(const Image& image) {
  auto width = static_cast<int>(image.empty() ? 0 : image[0].size());
  auto height = static_cast<int>(image.size());
  return {width, height};
}

bool IsPointInImage(Size image_size, int x, int y) {
      return y >= 0 && y < image_size.height && x >= 0 && x < image_size.width;
}



class Shape: public IShape {
public:


  void SetPosition(Point position_) override{
    position = position_;
  };

   Point GetPosition() const override{
    return position;
  };

   void SetSize(Size size_) override{
    size = size_;
  };

   Size GetSize() const override{
    return size;
  };

   void SetTexture(std::shared_ptr<ITexture> texture_) override{
    texture = std::move(texture_);
  };

   ITexture* GetTexture() const override{
    return texture.get();
  };

  // Рисует фигуру на указанном изображении
   void Draw(Image& image) const override{
    Point p;
    auto image_size = GetImageSize(image);
    for (p.y = 0; p.y < size.height; ++p.y) {
      for (p.x = 0; p.x < size.width; ++p.x) {
        if (IsPointInShape(p)) {
          char pixel = '.';
          if (texture && IsPointInImage(texture->GetSize(), p.x, p.y)) {
            pixel = texture->GetImage()[p.y][p.x];
          }
          Point dp = {position.x + p.x, position.y + p.y};
          if (IsPointInImage(image_size, dp.x, dp.y)) {
            image[dp.y][dp.x] = pixel;
          }
        }
      }
    }
  }
private:
    virtual bool IsPointInShape(Point) const = 0;
    Point position;
    Size size;
    std::shared_ptr<ITexture> texture;
};



class Rectangle: public Shape {
public:

  std::unique_ptr<IShape> Clone() const override{
    auto ptr = make_unique<Rectangle>(*this);
    return ptr;
  };

private:
    bool IsPointInShape(Point) const override {return true;}
};


class Ellipse: public Shape {
public:

  std::unique_ptr<IShape> Clone() const override{
    auto ptr = make_unique<Ellipse>(*this);
    return ptr;
  };

private:
     bool IsPointInShape(Point point) const override {
      return IsPointInEllipse(point, GetSize());
    }
};


unique_ptr<IShape> MakeShape(ShapeType shape_type) {
  if (shape_type == ShapeType::Rectangle) {
    return make_unique<Rectangle>();
  } else if (shape_type == ShapeType::Ellipse) {
    return make_unique<Ellipse>(); 
  } else {
    return nullptr;
  }
}