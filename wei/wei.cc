
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

#define NAMEA "GTS IDS GTS 4Q Cadence report- Oct.11.xlsx"
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


int main()
{
    time_t  start, load_end, read_end;
    xlnt::workbook wb;
    std::cout << "loading..." << std::endl;
    start = time(0);
    wb.load(NAMEA);
    load_end = time(0);

    // iterate sheet
    int sc = wb.sheet_count();
    std::cout << "There are " << sc << " sheets in this workbook" << std::endl;
    std::vector<std::string> sts = wb.sheet_titles();
    for (int i = 0; i < sc; i++) {
        xlnt::worksheet ws = wb.sheet_by_index(i);
        std::cout << "\t" << i << ": " << sts[i]
        << "(id:" << ws.id() << ", state:" << str_state(ws.sheet_state()) << ")" << std::endl;
    }


    // do active sheet
    xlnt::worksheet aws = wb.active_sheet();
    std::cout << "active sheet id is " << aws.id() << ", title is " << aws.title() << std::endl;

    // iterate sheet 3
    xlnt::worksheet ws2 = wb.sheet_by_index(1);
    std::cout << "now open sheet id " << ws2.id() << ", title " << ws2.title() << std::endl;
    std::cout << "\tfrom (" << ws2.lowest_column().column_string()
              << "-" << ws2.lowest_row() << ") to (" << ws2.highest_column().column_string()
              << "-" << ws2.highest_row() << ")" << std::endl;

    // loop cell in sheet
    for (xlnt::row_t row = ws2.lowest_row(); row <= ws2.highest_row(); ++row) {
        std::cout << "\trow " << row << " values:" << std::endl;
        for (xlnt::column_t col = ws2.lowest_column(); col <= ws2.highest_column(); ++col) {
            const xlnt::cell c = ws2.cell(col, row);
            if (c.data_type() == xlnt::cell_type::empty) {
                continue;
            }

            if (c.data_type() != xlnt::cell_type::shared_string) {
                continue;
            }
            std::cout << "\t\t" << col.column_string() << "(" << int(c.data_type())
            << "," << c.is_date() << "): "
                       << c.value<std::string>() << std::endl;
        }
    }
    read_end = time(0);
    std::cout << std::endl;
    std::cout << "Well run, load time " << load_end - start
              << "s, read time " << read_end - load_end << "s" << std::endl;
    return (0);
}
