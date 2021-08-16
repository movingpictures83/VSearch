#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "VSearchPlugin.h"

void VSearchPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 std::cout << inputfile << std::endl;
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
   std::string command = "export OLDPATH=${PATH}; ";
   command += "export PATH=${CONDA_HOME}/bin/:${PATH}; ";
   command += "eval \"$(conda shell.bash hook)\"; ";
   command += "conda activate qiime2-2021.4; ";
   std::string op = parameters["op"];
   if (op == "join-pairs") {
      command += "qiime vsearch join-pairs --i-demultiplexed-seqs "+myPrefix+"/"+parameters["inputfile"]+" ";
      if (parameters.count("minovlen") != 0)
	      command += "--p-minovlen "+parameters["minovlen"]+" ";
      if (parameters.count("maxdiffs") != 0)
	      command += "--p-maxdiffs "+parameters["maxdiffs"]+" ";
      command += "--o-joined-sequences "+file+"; ";
   }
   else if (op == "uchime-denovo") {
   command += "qiime vsearch "+parameters["op"]+" --i-table "+myPrefix+"/"+parameters["table"]+" --i-sequences "+myPrefix+"/"+parameters["sequences"]+" --o-chimeras "+file+"-chim-seqs.qza --o-nonchimeras "+file+"-nochim-seqs.qza --o-stats "+file+"-chim-stats.qza; ";
   }
   else if (op == "cluster-features-open-reference") {
   command += "qiime vsearch "+parameters["op"]+" --i-table "+myPrefix+"/"+parameters["table"]+" --i-sequences "+myPrefix+"/"+parameters["sequences"]+" --i-reference-sequences "+myPrefix+"/"+parameters["referencesequences"]+" --p-perc-identity "+parameters["percidentity"]+" --o-clustered-table "+file+"-table-or-97.qza --o-clustered-sequences "+file+"-rep-seqs-or-97.qza --o-new-reference-sequences "+file+"-new-ref-seqs-or-97.qza; ";
   }
 //std::cout << command << std::endl;


   command += "conda deactivate; ";
   command += "conda deactivate; ";
   command += "export PATH=${OLDPATH}";
 std::cout << command << std::endl;


 system(command.c_str());
}

PluginProxy<VSearchPlugin> VSearchPluginProxy = PluginProxy<VSearchPlugin>("VSearch", PluginManager::getInstance());
