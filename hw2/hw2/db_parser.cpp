#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include "db_parser.h"
#include "util.h"


using namespace std;


DBParser::DBParser()
{
    lineno_ = 1;
    error_ = false;

}
DBParser::~DBParser()
{
    for(map<string, SectionParser*>::iterator it = parsers_.begin();
            it != parsers_.end();
            ++it) {
        delete it->second;
    }
}
void DBParser::addSectionParser(const std::string& sectionName,
                                SectionParser*     parser)
{
    parsers_.insert(make_pair(sectionName, parser));
}
bool DBParser::parse(string db_filename, DataStore& ds)
{
#ifdef DEBUG
    cout << "Starting parsing" << endl;
#endif
    ifstream ifile(db_filename.c_str());
    if(ifile.fail()) {
        return true;
    }

    lineno_ = 1;
    int startLineNo;
    string line;
    string sectionName;
    PState state = FIND_SECTION;
    stringstream sectionText;
    while(!ifile.fail() && !error_) {
        getline(ifile, line);
#ifdef DEBUG
        cout << "Line: " << line << endl;
#endif
        trim(line); // remove whitespace on either end
        if(state == FIND_SECTION) {
            if((line.size() > 2) && line[0] == '<' && line[line.size()-1] == '>') {
                state = IN_SECTION;
                sectionName = line.substr(1,line.size()-2);
                startLineNo = lineno_ + 1;
#ifdef DEBUG
                cout << "Found section: " << sectionName << endl;
#endif
                sectionText.clear();
                sectionText.str("");
            }

        }
        else if(state == IN_SECTION) {
            if((line.size() > 3) && line[0] == '<' && line[1] == '/' && line[line.size()-1] == '>') {
                map<string, SectionParser*>::iterator it = parsers_.find(sectionName);
                if(it != parsers_.end()) {
                    error_ = it->second->parse(sectionText, ds, startLineNo, errorMsg_);
                    if(error_) {
                        lineno_ = startLineNo;
                    }

                }
                else {
                    cerr << "No section parser available for " << sectionName << "..skipping!" << endl;
                }
                state = FIND_SECTION;
#ifdef DEBUG
                cout << "End section: " << sectionName << endl;
#endif
            }
            else {
                sectionText << line << '\n';
            }
        }

        if(error_) {
            cerr << "Parse error on line " << lineno_ << ": " << errorMsg_ << endl;
        }
        lineno_++;
    }
    if(!error_) {
        for(map<string, SectionParser*>::iterator it = parsers_.begin();
                it != parsers_.end();
                ++it)
        {
            it->second->reportItemsRead(cout);
        }
    }
    return error_;
}

ProductSectionParser::ProductSectionParser()
{
    numRead_ = 0;
}
ProductSectionParser::~ProductSectionParser()
{
    for(map<string, ProductParser*>::iterator it = prodParsers_.begin();
            it != prodParsers_.end();
            ++it) {
        delete it->second;
    }
}

void ProductSectionParser::addProductParser(ProductParser* p)
{
    prodParsers_.insert(make_pair(p->categoryID(), p));
}


bool ProductSectionParser::parse(
    std::istream& is,
    DataStore& ds,
    int& lineno,
    std::string& errorMsg)
{
    string line;
    while(getline(is, line)) {
        stringstream ss(line);
        string category;
        ss >> category;
        map<string,ProductParser*>::iterator it = prodParsers_.find(category);
        if(it == prodParsers_.end()) {
            string msg = "No product parser available for category: ";
            errorMsg =  msg + category;
            return true;
        }
        lineno++;
        Product* p = parseProduct(category, is, lineno, errorMsg);
        if(p != NULL) {
            ds.addProduct(p);
            numRead_++;
        }
        else {
            return true;
        }
    }
    return false;
}


Product* ProductSectionParser::parseProduct(const string& category,
        istream& is,
        int& lineno,
        std::string& errorMsg)
{
    bool error = false;
    map<string,ProductParser*>::iterator it = prodParsers_.find(category);
    if(it != prodParsers_.end()) {
        return it->second->parse(category, is, error, errorMsg, lineno);
    }
    else {
        //error_ = true;
        string msg = "No product parser available for category: ";
        errorMsg =  msg + category;
        return NULL;
    }
}

void ProductSectionParser::reportItemsRead(std::ostream& os)
{
    os << "Read " << numRead_ << " products" << endl;
}

UserSectionParser::UserSectionParser()
{
    numRead_ = 0;
}
bool UserSectionParser::parse(
    std::istream& is,
    DataStore& ds,
    int& lineno,
    std::string& errorMsg)
{
    string line;
    while(getline(is, line)) {
        stringstream ss(line);
        User* u = parseUser(ss, ds, errorMsg);
        if(u) {
            ds.addUser(u);
            numRead_++;
        }
        else {
            return true;
        }
        lineno++;
    }
    return false;
}
User* UserSectionParser::parseUser(
    std::istream& is,
    DataStore& ds,
    std::string& errorMsg)
{
    string username;
    double balance;
    int type;
    is >> username;
    if( is.fail() ) {
        errorMsg = "Unable to read username";
        return NULL;
    }
    is >> balance;
    if( is.fail() ) {
        errorMsg = "Unable to read balance";
        return NULL;
    }
    is >> type;
    if( is.fail() ) {
        errorMsg = "Unable to read type";
        return NULL;
    }
    return new User(username, balance, type);
}

void UserSectionParser::reportItemsRead(std::ostream& os)
{
    os << "Read " << numRead_ << " users" << endl;
}

