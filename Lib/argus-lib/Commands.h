//----------------------------------------------------------------------------------------------------------------------
// Provides possible image processing Command interface implementations
// Created by Rozhkov Dmitrii rozhkovdmitrii@yandex.ru for Argus-soft on 09.08.2020.
//----------------------------------------------------------------------------------------------------------------------
#ifndef CommandsH
#define CommandsH
//----------------------------------------------------------------------------------------------------------------------
#include "CommonTypes.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
//----------------------------------------------------------------------------------------------------------------------
class LoadCommand : public ICommand
{
public:
  LoadCommand(const std::string & dstImageName, const std::string & srcFile);
  
  // ICommand
  void operator()(ImageMap & imageMap) const override;
  std::string toString() const override;

private:
  const std::string _dstImageName;
  const std::string _srcFile;
};
//----------------------------------------------------------------------------------------------------------------------
class StoreCommand : public ICommand
{
public:
  StoreCommand(const std::string & srcImageName, const std::string & dstFile);
  
  // ICommand
  void operator()(ImageMap & imageMap) const override;
  std::string toString() const override;

private:
  const std::string _srcImageName;
  const std::string _dstFile;
};
//----------------------------------------------------------------------------------------------------------------------
class DisplayCommand : public ICommand
{
public:
  DisplayCommand(const std::string & imageName);
  
  // ICommand
  void operator()(ImageMap & imageMap) const override;
  std::string toString() const override;

private:
  const std::string _imageName;
};
//----------------------------------------------------------------------------------------------------------------------
class BlurCommand : public ICommand
{
public:
  BlurCommand(const std::string & srcImageName, const std::string & dstImageName, int blurSize);
  
  // ICommand
  void operator()(ImageMap & imageMap) const override;
  std::string toString() const override;

private:
  std::string _srcImageName;
  std::string _dstImageName;
  int _blurSize;
};
//----------------------------------------------------------------------------------------------------------------------
class ResizeCommand : public ICommand
{
public:
  ResizeCommand(const std::string & srcImageName, const std::string & dstImageName, int newWidht, int newHeight);
  
  // ICommand
  void operator()(ImageMap & imageMap) const override;
  std::string toString() const override;
  
private:
  std::string _srcImageName;
  std::string _dstImageName;
  int _newWidth;
  int _newHeight;
};
//----------------------------------------------------------------------------------------------------------------------
}
#endif //CommandsH
