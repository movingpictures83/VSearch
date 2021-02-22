#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "VSearchPlugin.h"

void VSearchPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }
}

void VSearchPlugin::run() {
   
}

void VSearchPlugin::output(std::string file) {  
   std::string myPrefix = std::string(PluginManager::prefix());
   std::string command = "eval \"$(conda shell.bash hook)\"; ";
   command += "conda activate qiime2-2020.11; ";
   command += "qiime vsearch cluster-features-open-reference --i-table "+myPrefix+"/"+parameters["table"]+" --i-sequences "+myPrefix+"/"+parameters["sequences"]+" --i-reference-sequences "+myPrefix+"/"+parameters["referencesequences"]+" --p-perc-identity "+parameters["percidentity"]+" --o-clustered-table "+file+"-table-or-97.qza --o-clustered-sequences "+file+"-rep-seqs-or-97.qza --o-new-reference-sequences "+file+"-new-ref-seqs-or-97.qza; conda deactivate";
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<VSearchPlugin> VSearchPluginProxy = PluginProxy<VSearchPlugin>("VSearch", PluginManager::getInstance());
