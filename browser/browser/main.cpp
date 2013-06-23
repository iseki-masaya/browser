#include <libxml/HTMLparser.h>
#include <iostream>
#include <fstream>

using namespace std;

void FindInfo(xmlNode*& element);

int main() {
  //　HTML用の構造体
  htmlDocPtr m_doc;
	
  // ファイル名とエンコードの設定
  const char* file = "/tmp/sample/sample.html";
	const char* enc = "utf-8";
	
  // xmlの読み込み
	m_doc = htmlReadFile(file, enc, HTML_PARSE_RECOVER);
  if (m_doc) {
    htmlNodePtr root = xmlDocGetRootElement(m_doc);
    if (root != NULL) {
      FindInfo(root);
    }
    xmlFreeDoc(m_doc);
    m_doc = NULL;
  }
	
  xmlCleanupParser();
  xmlCleanupCharEncodingHandlers();
}

void FindInfo(xmlNode*& element) {
  for (htmlNodePtr node = element; node != NULL; node = node->next) {
    if (node->type == XML_ELEMENT_NODE) {
      /** もしノードの中身が「A」タグでattributeに「HREF」が含まれていれば表示 */
      if(xmlStrcasecmp(node->name, (const xmlChar*)"A") == 0){
        for(xmlAttrPtr attr = node->properties; attr != NULL; attr = attr->next){
          if(xmlStrcasecmp(attr->name, (const xmlChar*)"HREF") == 0){
            printf((char *)node->children->content, "%s\n");
          }
        }
      }
      if(node->children != NULL)
      {
        FindInfo(node->children);
      }
    }
  }
}