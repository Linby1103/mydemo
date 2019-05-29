#ifndef _TMPMATCH_H_
#define _TMPMATCH_H_
#include <iostream>
#include <vector>
class sampleClass{
public:
	int va;
	int vb;
	int vc;
	void sampleClassrest();
	sampleClass(){};
	sampleClass(int a, int b, int c) : va(a), vb(b), vc(c){}
	void SetVecVal();
	void printf_val();
	void SetVal(int va_, int vb_);
	void setTemp(sampleClass& class1);
	std::vector <sampleClass> pthis1;
	sampleClass* pThis2;
};
#endif