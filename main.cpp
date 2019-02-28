/** @author ligang
  * @date 20190228
**/
#include "stdio.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main(int argc, char *argv[])
{
    XMLDocument doc;
	doc.LoadFile(argv[1]);
    doc.SaveFile(argv[1]);

    return 0;
}