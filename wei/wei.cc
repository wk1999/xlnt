
#include <xlnt/xlnt.hpp>

int write_smpl()
{
    xlnt::workbook wb;
    xlnt::worksheet ws = wb.active_sheet();

    ws.cell("A1").value(700);
    ws.cell("B2").value("hello the world");
    ws.cell("C3").formula("=RAND()");

    ws.merge_cells("C3:D4");
    //ws.freeze_panes("B2");

    wb.save("sample.xlsx");

    return 0;
}

#include <iostream>
#include <time.h>

inline std::string str_state(xlnt::sheet_state st)
{
    switch(st) {
        case xlnt::sheet_state::visible:
            return "visible";
        case xlnt::sheet_state::hidden:
            return "hidden";
        case xlnt::sheet_state::very_hidden:
            return "very hidden";
        default:
            return "PAGE NO SETUP!!!!!!!!!!!!!!!!!!!";
    }
}

#include <unistd.h>
#include <dirent.h>
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
std::cout << "exe path:" << exe_path << std::endl;
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

    time_t  start, load_end, read_end;
    xlnt::workbook wb;
    std::cout << "loading " << xlsx << " ..." << std::flush;
    start = time(0);
    wb.load(xlsx);
    load_end = time(0);
    std::cout << "ok" << std::endl;
#if 0
    std::cout << "saveing..." << std::flush;
    xlsx += std::string(".1.xlsx");
    wb.save(xlsx);
    int s_end = time(0);
    std::cout << "ok" << std::endl;
    std::cout << "load time " << load_end-start << "s, save time " << s_end-load_end << "s" << std::endl;
    return (0);
#endif
    // iterate sheet
    int sc = wb.sheet_count();
    std::cout << "There are " << sc << " sheets in this workbook" << std::endl;
    std::vector<std::string> sts = wb.sheet_titles();
    for (int i = 0; i < sc; i++) {
        xlnt::worksheet ws = wb.sheet_by_index(i);
        std::cout << "\t" << i << ": " << sts[i]
        << "(id:" << ws.id() << ", visible:" << ws.sheet_visible() << ")" << std::endl;
    }


#if 0
    // do active sheet
    xlnt::worksheet aws = wb.active_sheet();
    std::cout << "active sheet id is " << aws.id() << ", title is " << aws.title() << std::endl;

    // iterate sheet 3
    int test_index = 1;
    if (test_index >= sc) {
        test_index = 0;
    }
    xlnt::worksheet ws2 = wb.sheet_by_index(test_index);
    std::cout << "now open sheet id " << ws2.id() << ", title " << ws2.title() << std::endl;
    std::cout << "\tfrom (" << ws2.lowest_column().column_string()
              << "-" << ws2.lowest_row() << ") to (" << ws2.highest_column().column_string()
              << "-" << ws2.highest_row() << ")" << std::endl;

    // loop cell in sheet
    for (xlnt::row_t row = ws2.lowest_row(); row <= ws2.highest_row(); ++row) {
        //std::cout << "\trow " << row << " values:" << std::endl;
        for (xlnt::column_t col = ws2.lowest_column(); col <= ws2.highest_column(); ++col) {
            const xlnt::cell c = ws2.cell(col, row);
            if (c.data_type() == xlnt::cell_type::empty) {
                continue;
            }
            c.dump_val(std::cout);
#if 0
            if (c.data_type() == xlnt::cell_type::shared_string) {
                std::cout << "\t\t" << col.column_string() << "(" << int(c.data_type())
                << "," << c.is_date() << "): "
                       << c.value<std::string>() << std::endl;
            }

            if (c.data_type() == xlnt::cell_type::shared_string) {
                std::cout << "\t\t" << col.column_string() << "(" << int(c.data_type())
                << "," << c.is_date() << "): "
                       << c.value<std::string>() << std::endl;
            }
#endif            
        }
    }
#endif

    read_end = time(0);
    std::cout << std::endl;
    std::cout << "Well run, load time " << load_end - start
              << "s, read time " << read_end - load_end << "s" << std::endl;

    // map<sheet_title, map<from_col, to_col> >
    typedef std::map<std::string, std::string> COL_MAP;
    typedef std::map<std::string, COL_MAP> SHEET_MAP;
    SHEET_MAP sheet_map;
    COL_MAP   col_map; //tmp for every sheet
#define TO_ZERO "ZERO"

    col_map["F"] = "J";
    col_map["K"] = TO_ZERO;
    col_map["AG"] = "AH";
    col_map["AI"] = TO_ZERO;
    col_map["BB"] = "BF";
    col_map["BG"] = TO_ZERO;
    col_map["AL"] = TO_ZERO;
    col_map["BX"] = "BY";
    col_map["BZ"] = TO_ZERO;
    sheet_map["TTL SUM"] = col_map;

    col_map.clear();
    col_map["I"] = "M";
    col_map["N"] = TO_ZERO;
    sheet_map["Sheet2"] = col_map;

    col_map.clear();
    col_map["J"] = "M";
    col_map["N"] = TO_ZERO;
    sheet_map["By Seller"] = col_map;

    col_map.clear();
    col_map["AF"] = "AJ";
    col_map["AK"] = TO_ZERO;
    sheet_map["IS Direct Rev"] = col_map;

    col_map.clear();
    col_map["F"] = "J";
    col_map["K"] = TO_ZERO;
    col_map["AF"] = "AJ";
    col_map["AK"] = TO_ZERO;
    sheet_map["IS Signing(LT500K)"] = col_map;

    col_map.clear();
    col_map["F"] = "J";
    col_map["K"] = TO_ZERO;
    col_map["AG"] = "AK";
    col_map["AL"] = TO_ZERO;
    sheet_map["IS Rev (PRC Comm)"] = col_map;

    col_map.clear();
    col_map["F"] = "J";
    col_map["K"] = TO_ZERO;
    col_map["AG"] = "AK";
    col_map["AL"] = TO_ZERO;
    sheet_map["IS Signing (PRC Comm) "] = col_map;

    col_map.clear();
    col_map["F"] = "G";
    col_map["H"] = TO_ZERO;
    col_map["AE"] = "AF";
    col_map["AG"] = TO_ZERO;
    sheet_map["IS Brand Format"] = col_map;

    col_map.clear();
    col_map["F"] = "G";
    col_map["H"] = TO_ZERO;
    col_map["K"] = "L";
    col_map["M"] = TO_ZERO;
    col_map["P"] = "Q";
    col_map["R"] = TO_ZERO;
    col_map["U"] = "V";
    col_map["W"] = TO_ZERO;
    col_map["Z"] = "AA";
    col_map["AB"] = TO_ZERO;
    col_map["AE"] = "AF";
    col_map["AG"] = TO_ZERO;
    col_map["AJ"] = "AK";
    col_map["AL"] = TO_ZERO;
    col_map["AO"] = "AP";
    col_map["AQ"] = TO_ZERO;
    col_map["AT"] = "AU";
    col_map["AV"] = TO_ZERO;
    col_map["AY"] = "AZ";
    col_map["BA"] = TO_ZERO;
    sheet_map["IS - Brand "] = col_map;

    col_map.clear();
    col_map["F"] = "J";
    col_map["K"] = TO_ZERO;
    col_map["AG"] = "AK";
    col_map["AL"] = TO_ZERO;
    sheet_map["TSS Rev (Comm)"] = col_map;

    col_map.clear();
    col_map["F"] = "J";
    col_map["K"] = TO_ZERO;
    col_map["AG"] = "AK";
    col_map["AL"] = TO_ZERO;
    sheet_map["TSS Signing (Comm)"] = col_map;

    col_map.clear();
    col_map["F"] = "J";
    col_map["K"] = TO_ZERO;
    col_map["AG"] = "AK";
    col_map["AL"] = TO_ZERO;
    sheet_map["LOGO Rev (ENT non-KAP)"] = col_map;

    col_map.clear();
    col_map["G"] = "K";
    col_map["L"] = TO_ZERO;
    col_map["AH"] = "AL";
    col_map["AM"] = TO_ZERO;
    sheet_map["LOGO Signing (ENT non-KAP)"] = col_map;

    // test copy F6 to J6 on "TTL SUM"
    SHEET_MAP::const_iterator sheet_it = sheet_map.begin();
    SHEET_MAP::const_iterator sheet_end = sheet_map.end();
    for (; sheet_it != sheet_end; ++sheet_it) {
        const auto & title = sheet_it->first;
        const auto & col_m = sheet_it->second;
        std::cout << "working " << title << "..." << std::flush;
        auto ws = wb.sheet_by_title(title);
        for (xlnt::row_t row = ws.lowest_row(); row <= ws.highest_row(); ++row) {
            COL_MAP::const_iterator col_it = col_m.begin();
            COL_MAP::const_iterator col_end = col_m.end();
            for (; col_it != col_end; ++col_it) {
                const auto & first = col_it->first;
                const auto & second = col_it->second;
                if (second == TO_ZERO) {
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
    xlsx += std::string("___new.xlsx");
    std::cout << "save to " << xlsx << "..." << std::flush;
    wb.save(xlsx);
    std::cout << "ok" << std::endl;
    int save_end = time(0);
    std::cout << "save time " << save_end - read_end << "s. finished BYE." << std::endl;
    return (0);
}
