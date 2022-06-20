#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

//Original code from https://semidtor.wordpress.com/2012/12/15/readwrite-xml-file-with-rapidxml/

using namespace rapidxml;

int main()
{
	//declaration node
	xml_document<> doc;
	xml_node<>* decl = doc.allocate_node(node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
	doc.append_node(decl);

	//append root node to node declaration
	xml_node<>* root = doc.allocate_node(node_element, "rootnode");
	root->append_attribute(doc.allocate_attribute("version", "1.0"));
	root->append_attribute(doc.allocate_attribute("type", "example"));
	doc.append_node(root);

	//append child node to root node
	xml_node<>* child = doc.allocate_node(node_element, "childnode");
	root->append_node(child);

	//append data node to childnode
	xml_node<>* data = doc.allocate_node(node_element, "data");
	data->append_attribute(doc.allocate_attribute("encoding", "csv"));
	std::string dataString = 
		std::string("\n") +
		"Hi! This is the data inside\n" +
		"the data node" +
		std::string("\n\t\t");
	data->value(dataString.c_str());
	child->append_node(data);

	// Convert doc to string if needed
	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	// Save to file
	std::ofstream file_stored("xmlSaveData/file_stored.xml");
	file_stored << doc;
	file_stored.close();
	doc.clear();

	return 0;
}