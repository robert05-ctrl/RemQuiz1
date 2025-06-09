#include "FileManagerForm.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#using <Microsoft.VisualBasic.dll>
#include <msclr/marshal_cppstd.h>

namespace FlashnotesGUI {

FileManagerForm::FileManagerForm(flashnotes::FileController* ctrl)
{
    controller = ctrl;
    Dock = DockStyle::Fill;

    tree = gcnew TreeView();
    tree->Dock = DockStyle::Fill;

    FlowLayoutPanel^ bar = gcnew FlowLayoutPanel();
    bar->Dock = DockStyle::Bottom;

    btnAddFile = gcnew Button();
    btnAddFile->Text = "Add File";
    btnAddFile->Click += gcnew EventHandler(this, &FileManagerForm::onAddFile);

    btnAddFolder = gcnew Button();
    btnAddFolder->Text = "Add Folder";
    btnAddFolder->Click += gcnew EventHandler(this, &FileManagerForm::onAddFolder);

    btnOpen = gcnew Button();
    btnOpen->Text = "Open";
    btnOpen->Click += gcnew EventHandler(this, &FileManagerForm::onOpen);

    btnDelete = gcnew Button();
    btnDelete->Text = "Delete";
    btnDelete->Click += gcnew EventHandler(this, &FileManagerForm::onDelete);

    bar->Controls->AddRange(gcnew cli::array<Control^>{btnAddFile, btnAddFolder, btnOpen, btnDelete});

    Controls->Add(tree);
    Controls->Add(bar);

    loadData();
}

void FileManagerForm::loadData()
{
    tree->Nodes->Clear();
    auto foldersRes = controller->listFolders();
    auto filesRes = controller->listFiles();
    if (!foldersRes || !filesRes) return;
    auto folders = foldersRes.value();
    auto files = filesRes.value();

    System::Collections::Generic::Dictionary<int, TreeNode^>^ nodes = gcnew System::Collections::Generic::Dictionary<int, TreeNode^>();
    for (const auto& f : folders) {
        TreeNode^ n = gcnew TreeNode(gcnew String(f.name.c_str()));
        n->Tag = System::Tuple::Create(true, f.id);
        nodes[f.id] = n;
        if (f.parentId == -1) tree->Nodes->Add(n);
    }
    for (const auto& f : folders) {
        if (f.parentId != -1 && nodes->ContainsKey(f.parentId))
            nodes[f.parentId]->Nodes->Add(nodes[f.id]);
    }

    for (const auto& m : files) {
        TreeNode^ node = gcnew TreeNode(gcnew String(m.title.c_str()));
        node->Tag = System::Tuple::Create(false, m.id);
        if (m.folderId != -1 && nodes->ContainsKey(m.folderId))
            nodes[m.folderId]->Nodes->Add(node);
        else
            tree->Nodes->Add(node);
    }
    tree->ExpandAll();
}

void FileManagerForm::onAddFile(Object^ sender, EventArgs^ e)
{
    OpenFileDialog^ dlg = gcnew OpenFileDialog();
    if (dlg->ShowDialog() == DialogResult::OK) {
        int folderId = -1;
        if (tree->SelectedNode && safe_cast<System::Tuple<bool,int>^>(tree->SelectedNode->Tag)->Item1)
            folderId = safe_cast<System::Tuple<bool,int>^>(tree->SelectedNode->Tag)->Item2;
        auto res = controller->createFile(msclr::interop::marshal_as<std::string>(dlg->FileName), folderId);
        if (!res)
            MessageBox::Show(gcnew String(res.error().c_str()));
        loadData();
    }
}

void FileManagerForm::onAddFolder(Object^ sender, EventArgs^ e)
{
    String^ name = Microsoft::VisualBasic::Interaction::InputBox("Folder name", "New Folder");
    if (!String::IsNullOrWhiteSpace(name)) {
        int parentId = -1;
        if (tree->SelectedNode && safe_cast<System::Tuple<bool,int>^>(tree->SelectedNode->Tag)->Item1)
            parentId = safe_cast<System::Tuple<bool,int>^>(tree->SelectedNode->Tag)->Item2;
        auto res = controller->createFolder(msclr::interop::marshal_as<std::string>(name), parentId);
        if (!res)
            MessageBox::Show(gcnew String(res.error().c_str()));
        loadData();
    }
}

void FileManagerForm::onOpen(Object^ sender, EventArgs^ e)
{
    if (!tree->SelectedNode) return;
    auto tag = safe_cast<System::Tuple<bool,int>^>(tree->SelectedNode->Tag);
    if (!tag->Item1) {
        auto files = controller->listFiles();
        if (!files) return;
        for (const auto& m : files.value()) {
            if (m.id == tag->Item2) {
                System::Diagnostics::Process::Start(gcnew String(m.path.c_str()));
                break;
            }
        }
    }
}

void FileManagerForm::onDelete(Object^ sender, EventArgs^ e)
{
    if (!tree->SelectedNode) return;
    auto tag = safe_cast<System::Tuple<bool,int>^>(tree->SelectedNode->Tag);
    if (tag->Item1) {
        controller->removeFolder(tag->Item2);
    } else {
        controller->removeFile(tag->Item2);
    }
    loadData();
}

} // namespace FlashnotesGUI
