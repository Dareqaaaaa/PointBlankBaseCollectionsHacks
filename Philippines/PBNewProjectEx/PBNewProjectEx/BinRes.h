#ifndef _waxie_binary_resource_h_
#define _waxie_binary_resource_h_

#include <string>

class BinRes
{
public:
	BinRes();
	virtual ~BinRes();

public:
	static void ExtractBinResource(std::string strCustomResName, int nResourceId, std::string strOutputName);

private:
	static std::string getAppLocation();

};

#endif 
