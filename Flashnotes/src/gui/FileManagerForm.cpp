#include "FileManagerForm.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include <msclr/marshal_cppstd.h>


namespace FlashnotesGUI {

FileManagerForm::FileManagerForm(flashnotes::FileController* ctrl)
{
    controller = ctrl;
    Dock = DockStyle::Fill;

    fileList = gcnew ListView();
    fileList->Dock = DockStyle::Fill;

    btnAdd = gcnew Button();
    btnAdd->Text = "Add";
    btnAdd->Dock = DockStyle::Bottom;
    btnAdd->Click += gcnew EventHandler(this, &FileManagerForm::onAdd);

    Controls->Add(fileList);
    Controls->Add(btnAdd);
}

void FileManagerForm::onAdd(Object^ sender, EventArgs^ e)
{
    OpenFileDialog^ dlg = gcnew OpenFileDialog();
    if (dlg->ShowDialog() == DialogResult::OK) {
        auto res = controller->createFile(); // placeholder
        if (!res)
            MessageBox::Show(gcnew String(res.error().c_str()));
        else
            fileList->Items->Add(gcnew ListViewItem(gcnew String(std::to_string(res.value().id).c_str())));
    }
}

} // namespace FlashnotesGUI
