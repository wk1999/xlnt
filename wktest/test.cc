
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

#define NAMEA "IPOS 5G Development Tasks.xlsx"
#include <iostream>

int main()
{
    xlnt::workbook wb;
    wb.load(NAMEA);

    // iterate sheet
    int sc = wb.sheet_count();
    std::cout << "There are " << sc << " sheets in this workbook" << std::endl;
    std::vector<std::string> sts = wb.sheet_titles();
    for (int i = 0; i < sc; i++) {
        std::cout << "    " << i << ": " << sts[i] << std::endl;
    }


    // do active sheet
    xlnt::worksheet aws = wb.active_sheet();
    std::cout << "active sheet id is " << aws.id() << ", title is " << aws.title() << std::endl;

    // iterate sheet 3
    xlnt::worksheet ws2 = wb.sheet_by_index(2);
    std::cout << "now open sheet id " << ws2.id() << ", title " << ws2.title() << std::endl;
    std::cout << "\tfrom (" << ws2.lowest_column().column_string()
              << "-" << ws2.lowest_row() << ") to (" << ws2.highest_column().column_string()
              << "-" << ws2.highest_row() << ")" << std::endl;

    // loop cell in sheet
    for (xlnt::row_t row = ws2.lowest_row(); row <= ws2.highest_row(); ++row) {
        std::cout << "\trow " << row << " values:" << std::endl;
        for (xlnt::column_t col = ws2.lowest_column(); col <= ws2.highest_column(); ++col) {
            const xlnt::cell c = ws2.cell(col, row);
            std::cout << "\t\t" << col.column_string() << "(" << int(c.data_type())
            << "," << c.is_date() << "): "
                       << c.value<std::string>() << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Well run" << std::endl;
    return (0);
}
