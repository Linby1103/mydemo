#ifndef _IMAGEINFO_H_
#define _IMAGEINFO_H_
//#include "../header/yjhvision/include.h"
#include "Image.h"
class pImgInfo
{
public:
	pImgInfo(){ reset(); }
	void reset();
	/*¥Ú”°imageœÍœ∏*/
	void printInfo(Mat Arrarinput, string imgName);
public:
	int image_width;
	int image_height;
	int image_channels;

};
template<class T0> class Creator
{
public:
	static T0 *create(const std::string &cls_id)
	{
		return creators.find(cls_id) == creators.end() ? 0 : creators[cls_id]->create();
	}
	static std::vector<std::string> enum_names() { std::vector<std::string> names; for (typename std::map<std::string, Creator*>::iterator iter = creators.begin(); iter != creators.end(); iter++) names.push_back(iter->first); return names; }
protected:
	virtual T0 *create() { return 0; }
	static std::map<std::string, Creator*> creators;
};

template<class T0, class T1> class ExtCreator : public Creator<T0>
{
public:
	ExtCreator(const std::string &cls_id) { this->creators[cls_id] = this; }
protected:
	virtual T0 *create() { return new T1(); }
};
	class TarModel
	{
	public:
		std::string	mdl_type;
		int pic_num;
		std::vector<cv::Point> msk_verts;
		int use_preproc;

		virtual void reset() = 0;
		virtual void copy_to(TarModel *other) = 0;
		// virtual void textize(TagFile &tf, const std::string &sect_id, int load) = 0;
		virtual ~TarModel() {};
	};
#define SPECIALIZE_BASE(base_cls) template<> std::map<std::string, Creator<base_cls>*> Creator<base_cls>::creators = std::map<std::string, Creator<base_cls>*>()
SPECIALIZE_BASE(TarModel);




#endif

