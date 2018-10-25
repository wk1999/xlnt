
#include <xlnt/xlnt.hpp>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <assert.h>

using namespace std;
vector<string> getFiles(string cate_dir)
{
	vector<string> files;//存放文件名
 
#ifdef WIN32
	_finddata_t file;
	long lf;
	//输入文件夹路径
	if ((lf=_findfirst(cate_dir.c_str(), &file)) == -1) {
		cout<<cate_dir<<" not found!!!"<<endl;
	} else {
		while(_findnext(lf, &file) == 0) {
			//输出文件名
			//cout<<file.name<<endl;
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
				continue;
			files.push_back(file.name);
		}
	}
	_findclose(lf);
#else
 
	DIR *dir;
	struct dirent *ptr;
	//char base[1000];
 
	if ((dir=opendir(cate_dir.c_str())) == NULL)
        {
		perror("Open dir error...");
                exit(1);
        }
 
	while ((ptr=readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
		        continue;
		else if(ptr->d_type == 8)    ///file
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
			files.push_back(ptr->d_name);
		else if(ptr->d_type == 10)    ///link file
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
			continue;
		else if(ptr->d_type == 4)    ///dir
		{
			//files.push_back(ptr->d_name);
			/*
		        memset(base,'\0',sizeof(base));
		        strcpy(base,basePath);
		        strcat(base,"/");
		        strcat(base,ptr->d_nSame);
		        readFileList(base);
			*/
		}
	}
	closedir(dir);
#endif
 
	sort(files.begin(), files.end());
	return files;
}

class string_asc_code
{
public:
    std::size_t operator()(const std::string & k) const
    {
        std::size_t v = 0;
        for (std::string::const_iterator it = k.begin(); it != k.end(); ++it) {
            v = (v << 8) + *it;
        }
        return (v);
    }
};

class col_less {
public:
    bool operator()(const std::string & x, const std::string & y) const
    {
        string_asc_code asc;
        return (asc(x) < asc(y));
    }
};

class config_map
{
public:
    // map<sheet_title, map<from_col, to_col> >
    // <from_col, to_col>, the 2nd must be greater than 1st
    // seems the ordering here is not needed.
    typedef std::map<std::string, std::string, col_less> COL_MAP;
    typedef std::map<std::string, COL_MAP> SHEET_MAP;
    const static std::string ZERO;
    const SHEET_MAP & get() const {
        return (sheet_map);
    }

private:
    SHEET_MAP sheet_map;
    COL_MAP   col_map; //tmp for every sheet

public:
    config_map() {
        col_map["F"] = "J";
        col_map["K"] = ZERO;
        col_map["AG"] = "AH";
        col_map["AI"] = ZERO;
        col_map["BB"] = "BF";
        col_map["BG"] = ZERO;
        col_map["AL"] = ZERO;
        col_map["BX"] = "BY";
        col_map["BZ"] = ZERO;
        sheet_map["TTL SUM"] = col_map;

        col_map.clear();
        col_map["I"] = "M";
        col_map["N"] = ZERO;
        sheet_map["Sheet2"] = col_map;

        col_map.clear();
        col_map["J"] = "M";
        col_map["N"] = ZERO;
        sheet_map["By Seller"] = col_map;

        col_map.clear();
        col_map["AF"] = "AJ";
        col_map["AK"] = ZERO;
        sheet_map["IS Direct Rev"] = col_map;

        col_map.clear();
        col_map["F"] = "J";
        col_map["K"] = ZERO;
        col_map["AF"] = "AJ";
        col_map["AK"] = ZERO;
        sheet_map["IS Signing(LT500K)"] = col_map;

        col_map.clear();
        col_map["F"] = "J";
        col_map["K"] = ZERO;
        col_map["AG"] = "AK";
        col_map["AL"] = ZERO;
        sheet_map["IS Rev (PRC Comm)"] = col_map;

        col_map.clear();
        col_map["F"] = "J";
        col_map["K"] = ZERO;
        col_map["AG"] = "AK";
        col_map["AL"] = ZERO;
        sheet_map["IS Signing (PRC Comm) "] = col_map;

        col_map.clear();
        col_map["F"] = "G";
        col_map["H"] = ZERO;
        col_map["AE"] = "AF";
        col_map["AG"] = ZERO;
        sheet_map["IS Brand Format"] = col_map;

        col_map.clear();
        col_map["F"] = "G";
        col_map["H"] = ZERO;
        col_map["K"] = "L";
        col_map["M"] = ZERO;
        col_map["P"] = "Q";
        col_map["R"] = ZERO;
        col_map["U"] = "V";
        col_map["W"] = ZERO;
        col_map["Z"] = "AA";
        col_map["AB"] = ZERO;
        col_map["AE"] = "AF";
        col_map["AG"] = ZERO;
        col_map["AJ"] = "AK";
        col_map["AL"] = ZERO;
        col_map["AO"] = "AP";
        col_map["AQ"] = ZERO;
        col_map["AT"] = "AU";
        col_map["AV"] = ZERO;
        col_map["AY"] = "AZ";
        col_map["BA"] = ZERO;
        sheet_map["IS - Brand "] = col_map;

        col_map.clear();
        col_map["F"] = "J";
        col_map["K"] = ZERO;
        col_map["AG"] = "AK";
        col_map["AL"] = ZERO;
        sheet_map["TSS Rev (Comm)"] = col_map;

        col_map.clear();
        col_map["F"] = "J";
        col_map["K"] = ZERO;
        col_map["AG"] = "AK";
        col_map["AL"] = ZERO;
        sheet_map["TSS Signing (Comm)"] = col_map;

        col_map.clear();
        col_map["F"] = "J";
        col_map["K"] = ZERO;
        col_map["AG"] = "AK";
        col_map["AL"] = ZERO;
        sheet_map["LOGO Rev (ENT non-KAP)"] = col_map;

        col_map.clear();
        col_map["G"] = "K";
        col_map["L"] = ZERO;
        col_map["AH"] = "AL";
        col_map["AM"] = ZERO;
        sheet_map["LOGO Signing (ENT non-KAP)"] = col_map;
    }
};

const std::string config_map::ZERO("ZERO");

class sheet_visitor : public xlnt::workstream_visitor {
    const config_map & _conf;
    const config_map::COL_MAP * _col;

    // cell attr
    std::string _cell_ref;
    bool    _cell_is_number;

    // value operation
    static const int _op_read = 0;
    static const int _op_write = 1;
    static const int _op_non = 2;
    int _op;
    config_map::COL_MAP _buf;
    std::string * _read_buf;
    const std::string * _write_buf;
public:
    sheet_visitor(const config_map & conf):_conf(conf), _col(NULL),
        _cell_is_number(true),_op(_op_non),
        _read_buf(NULL), _write_buf(NULL) {
        const config_map::SHEET_MAP & sheet_map = _conf.get();
        config_map::SHEET_MAP::const_iterator sheet_it = sheet_map.begin();
        config_map::SHEET_MAP::const_iterator sheet_end = sheet_map.end();
        col_less    cl;
        for (; sheet_it != sheet_end; ++sheet_it) {
            const auto & title = sheet_it->first;
            const auto & col_m = sheet_it->second;
            config_map::COL_MAP::const_iterator col_it = col_m.begin();
            config_map::COL_MAP::const_iterator col_end = col_m.end();
            for (; col_it != col_end; ++col_it) {
                if (col_it->second == config_map::ZERO) {
                    continue;
                }
                if (!cl(col_it->first, col_it->second)) {
                    std::cout << "In sheet [" << title << "] col [" << col_it->first;
                    std::cout << "] greater than [" << col_it->second << "] ";
                    std::cout << ": cannot support stream. EXIT" << std::endl;
                    assert(0);
                }
            }
        }
    }
    virtual void before_visit(const std::string & visit_name, const void * data) {
        std::cout << "I am visiting " << visit_name << std::endl;

        if (!data) {
            std::cout << "why no sheet data here?" << std::endl;
            assert(0);
        }

        const xlnt::workstream_type_sheet * sheet_data = (const xlnt::workstream_type_sheet*)data;
        std::cout << "name=" << sheet_data->get_name() << ", id=" << sheet_data->get_sheet_id();
        std::cout << ", state=" << sheet_data->get_state() << ", rid=" << sheet_data->get_r_id() << std::endl;

        const config_map::SHEET_MAP & sheet_map = _conf.get();
        config_map::SHEET_MAP::const_iterator it = sheet_map.find(sheet_data->get_name());
        if (sheet_map.end() != it) {
            std::cout << "\thandling..." << std::endl;
            _col = &(it->second);
            _buf.clear();
            _buf[config_map::ZERO] = "0";
        }
    }
    virtual void after_visit(const std::string & visit_name) {
        std::cout << "End of visiting " << visit_name << std::endl;
        _col = NULL;
    }
    virtual visit_actions start_element(const std::string & element, std::string & newval)
    {
        if (!_col) {
            return (WRITE);
        }

        const xlnt::workstream_path_stack & stack = get_path_stack();
        if (stack == "sheetData/row/c") {
            _cell_is_number = true;
            return (WRITE);
        }
        if (stack != "sheetData/row/c/v") {
            return (WRITE);
        }

        _op = _op_non;
        //std::cout << "cell(" << _cell_ref << "):" << _cell_is_number << std::endl;
        if (_cell_is_number) {
            std::pair<std::string, xlnt::row_t> ref = xlnt::cell_reference::split_reference(_cell_ref);
            const std::string & col = ref.first;
            // check this col is in config col
            config_map::COL_MAP::const_iterator col_it = _col->find(col);
            if ( col_it != _col->end()) {
                const std::string & col_to = col_it->second;
                if (col_to == config_map::ZERO) {
                    _op = _op_write;
                    _write_buf = &_buf[col_to];
                } else {
                    _op = _op_read; // get value
                    _read_buf = &_buf[col_to];
                }
            } else {
                // check this col is in buf map
                col_it = _buf.find(col);
                if ( col_it != _buf.end()) {
                    _op = _op_write;
                    _write_buf = &(col_it->second);
                }
            }
        }

        //debug
        if (_op != _op_non) {
            std::cout << _cell_ref << ":[";
            if (_op == _op_read) {
                std::cout << "read";
            } else {
                std::cout << "write:" << *_write_buf;
            }
            std::cout << "]" << std::endl;
        }
        return (WRITE);
    }
    virtual void end_element()
    {
        _op = _op_non;
    }
    virtual visit_actions start_attribute(const std::string & attr, std::string & newval)
    {
        if (!_col) {
            return (WRITE);
        }

        const xlnt::workstream_path_stack & stack = get_path_stack();
        if (stack == "sheetData/row/c/t") {
            _cell_is_number = false;
        }
        return (WRITE);
    }
    virtual void end_attribute()
    {
        if (!_col) {
            return;
        }
        // nothing to do
    }
    virtual visit_actions character(const std::string & value, std::string & newval)
    {
        if (!_col) {
            return (WRITE);
        }

        visit_actions act = WRITE;
        const xlnt::workstream_path_stack & stack = get_path_stack();
        if (stack == "sheetData/row/c/v") {
            if (_op == _op_read) {
                *_read_buf = value;
            } else if (_op == _op_write) {
                newval = *_write_buf;
                act = REPLACE;
            }
        } else if (stack == "sheetData/row/c/r") {
            _cell_ref = value;
        }
        return (act);
    }
};

void stream_test(const std::string & file, const config_map & cmap)
{
    std::cout << "stream test file: " << file << std::endl;
    xlnt::workstream_visitor visitor;
    sheet_visitor   sheet_visitor(cmap);
    xlnt::workstream_visitor_group visitors(file+"_100.xlsx");
    visitors.add_default_visitor(visitor);
    visitors.add_visitor(xlnt::relationship_type::worksheet, sheet_visitor);
    xlnt::workstream  ws;
    int result;
    result = ws.load(file);
    std::cout << "load result: " << result << std::endl;
    result = ws.visit(visitors);
    std::cout << "visit result: " << result << std::endl;
}

void workbook_test(const std::string & xlsx, const config_map & cmap)
{
    xlnt::workbook wb;
    std::cout << "loading " << xlsx << " ..." << std::flush;
    wb.load(xlsx);
    std::cout << "ok" << std::endl;

    // iterate sheet
    int sc = wb.sheet_count();
    std::cout << "There are " << sc << " sheets in this workbook" << std::endl;
    std::vector<std::string> sts = wb.sheet_titles();
    for (int i = 0; i < sc; i++) {
        xlnt::worksheet ws = wb.sheet_by_index(i);
        std::cout << "\t" << i << ": " << sts[i]
        << "(id:" << ws.id() << ", visible:" << ws.sheet_visible() << ")" << std::endl;
    }

    // test copy F6 to J6 on "TTL SUM"
    const config_map::SHEET_MAP & sheet_map = cmap.get();
    config_map::SHEET_MAP::const_iterator sheet_it = sheet_map.begin();
    config_map::SHEET_MAP::const_iterator sheet_end = sheet_map.end();
    for (; sheet_it != sheet_end; ++sheet_it) {
        const auto & title = sheet_it->first;
        const auto & col_m = sheet_it->second;
        std::cout << "working " << title << "..." << std::flush;
        auto ws = wb.sheet_by_title(title);
        for (xlnt::row_t row = ws.lowest_row(); row <= ws.highest_row(); ++row) {
            config_map::COL_MAP::const_iterator col_it = col_m.begin();
            config_map::COL_MAP::const_iterator col_end = col_m.end();
            for (; col_it != col_end; ++col_it) {
                const auto & first = col_it->first;
                const auto & second = col_it->second;
                if (second == config_map::ZERO) {
                    auto c = ws.cell(first, row);
                    if (c.data_type() == xlnt::cell_type::number) {
                        c.value(0);
                    }
                } else {
                    const auto c1 = ws.cell(first, row);
                    auto c2 = ws.cell(second, row);
                    if (c1.data_type() == xlnt::cell_type::number) {
                        c2.value(c1.value<double>());
                    }
                }
            }
        }
        std::cout << "ok" << std::endl;
    }
    std::cout << "saving ..." << std::flush;
    wb.save(xlsx+"___new.xlsx");
    std::cout << "ok" << std::endl;
}

#define STREAM_TEST
//#define WORKBOOK_TEST

int main(int argc, char** argv)
{
    std::string xlsx;

    if (1 == argc) {
        std::size_t i = 0;
        std::string exe_path;
        char * me = argv[0];
        char * slash = strrchr(me, '/');
        if (slash) {
            *slash = 0;
            exe_path = me;
        } else {
            exe_path = ".";
        }
        std::vector<std::string> files = getFiles(exe_path);
        for (; i < files.size(); i++) {
            const char * ext = strrchr(files[i].c_str(), '.');
            if (ext) {
                ext++;
                if (0 == strcmp(ext, "xlsx") || 0 == strcmp(ext, "xls")) {
                    xlsx = exe_path + "/" + files[i];
                    break;
                }
            }
        }
        if (i == files.size()) {
            std::cout << "no excel files were found, BYE" << std::endl;
            return (0);
        }
    } else if (2 == argc) {
        xlsx = argv[1];
    } else {
        std::cout << "please input an excel file as param" << std::endl;
        return (1);
    }

    time_t  start, end;
    config_map  cmap;
#ifdef STREAM_TEST
    std::cout << "streaming excel file: " << xlsx << std::endl;
    start = time(0);
    stream_test(xlsx, cmap);
    end = time(0);
    std::cout << "streamed excel file: " << xlsx << " in " << end-start << " seconds. BYE" << std::endl;
#endif
    std::cout << std::endl;
#ifdef WORKBOOK_TEST
    std::cout << "parsing excel file: " << xlsx << std::endl;
    start = time(0);
    workbook_test(xlsx, cmap);
    end = time(0);
    std::cout << "parsed excel file: " << xlsx << " in " << end-start << " seconds. BYE" << std::endl;
#endif
    
    return 0;
}
