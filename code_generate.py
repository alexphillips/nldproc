#!/usr/bin/python2

import glob;
import sys;

bannerStrings = [ "/**********************************************/",
                  "/* NLDPROC - Generated Code (code_generate.py */",
                  "/**********************************************/" ]


banner = "\n".join(bannerStrings)+"\n\n";

def generateProcessorHeader():
    headers = glob.glob("src/processors/*.h")
    writable_headers = []
    for header in headers:
        header = header.split("src/processors/")[1]
        if(header != "processor.h") and ( header!="processors.h"):
            writable_headers.append( header )
    file = open("src/processors/processors.h", "w")

    file.write(banner)
    file.write('#pragma once\n')
    file.write('#include "processor.h"\n')
    for header in writable_headers:
        print("   - " + header )
        file.write('#include "' + header +'"\n')

def generateTestHeader():
    headers = glob.glob("src/tests/*.h")
    writable_headers = []
    for header in headers:
        header = header.split("src/")[1]
        writable_headers.append(header)

    file = open("src/test_includes.h", "w")

    file.write(banner)
    defines = []
    for header in writable_headers:
        define = header.split(".")[0].split("/")[1]
        defines.append(define)
        print("   - " + header )
        file.write('#if NLDPROC_CURRENT_TEST == ' + define + '\n')
        file.write('\t#include "' + header +'"\n')
        file.write('#endif\n')

    print("   -> building all_reports")
    generateAllReportsScript(defines)

def generateAllReportsScript(defines):
    file =open("all_reports","w")
    file.write("#!/bin/bash\n")
    file.write("set -e\n")
    index = open("reports/index.html","w")
    index.write("<body style='background-color:#000;color:#fff;font-face:monospace;' ><center><h1>test results</h1>");
    for define in defines:
        print("          (" + define + ")")
        file.write("./build "+define+" 1\n")
        index.write("<img style='padding-bottom:100px;' src='" + define + ".raw.png'><br/>")
    index.write("</body></center>") 

def generateTestDefine():
    try:
        if(sys.argv[1]):
            file=open("src/test.h","w")
            file.write(banner)
            file.write('#define NLDPROC_CURRENT_TEST ' + sys.argv[1])
    except:
        pass


   
print("[ Code Generation ]")
print(" configuring processors ...")
generateProcessorHeader()
print(" configuring tests ...")
generateTestHeader()
print(" configuring active test...")
generateTestDefine()
print("[ complete ]")

