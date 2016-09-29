#include "provided.h"
#include <string>
#include "http.h"
using namespace std;

bool WebSteg::hideMessageInPage(const string& url, const string& msg, string& host)
{
	string webPage;
	if (!HTTP().get(url, webPage)){
		return false;
	}
	if (!Steg::hide(webPage, msg, host)){
		return false;
	}
	return true;
}

bool WebSteg::revealMessageInPage(const string& url, string& msg)
{
	string webPage;
	if (!HTTP().get(url, webPage)){
		return false;
	}
	if (!Steg::reveal(webPage, msg)){
		return false;
	}
	return true;
}
