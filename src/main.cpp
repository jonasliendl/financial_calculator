// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "./pendlerpauschale/CommuterBenefitCalculator.h"

enum View
{
    Start,
    Pendlerpauschale,
    Zinsen,
    Rendite,
    Prozent
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnBack(wxCommandEvent &event);
    void OnOpenPendlerpauschaleView(wxCommandEvent &event);
    void OnOpenZinsenView(wxCommandEvent &event);
    void OnOpenRenditeView(wxCommandEvent &event);
    void OnOpenProzentView(wxCommandEvent &event);
    void OnCalculateCommuterBenefit(wxCommandEvent &event);
    void ShowStartView();
    void ShowPendlerpauschaleView();
    void ShowZinsenView();
    void ShowRenditeView();
    void ShowProzentView();
    void RenderBackButton(wxBoxSizer *vbox);
    // Window properties
    wxString title;
    wxPoint startPoint;
    wxSize windowSize;
    // Routing
    View currentView;
    // Inputs
    wxTextCtrl *workingDaysInput;
    wxTextCtrl *commuteInKmInput;
    wxDECLARE_EVENT_TABLE();
};
enum
{
    ID_Hello = 1,
    ID_OpenPendlerpauschaleView = 2,
    ID_OpenZinsenView = 3,
    ID_OpenRenditeView = 4,
    ID_OpenProzentView = 5,
    ID_WorkingDaysInput = 6,
    ID_CommuteInKmInput = 7,
    ID_CalculateBenefitButton = 8,
    ID_BackButton = 9
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
        EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
            EVT_BUTTON(ID_OpenPendlerpauschaleView, MyFrame::OnOpenPendlerpauschaleView)
                EVT_BUTTON(ID_OpenZinsenView, MyFrame::OnOpenZinsenView)
                    EVT_BUTTON(ID_OpenRenditeView, MyFrame::OnOpenRenditeView)
                        EVT_BUTTON(ID_OpenProzentView, MyFrame::OnOpenProzentView)
                            EVT_BUTTON(ID_BackButton, MyFrame::OnBack)
                                EVT_BUTTON(ID_CalculateBenefitButton, MyFrame::OnCalculateCommuterBenefit)
                                    wxEND_EVENT_TABLE()

                                        wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Financial Calculator", wxPoint(50, 50), wxSize(700, 500));
    frame->Show(true);
    return true;
}
MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    this->title = title;
    this->startPoint = pos;
    this->windowSize = size;

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    ShowStartView();
    this->currentView = Start;
}
void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("Mit dieser Anwendungen können einige Berechnungen im Bereich Finanzen durchgeführt werden.",
                 "About Financial Calculator", wxOK | wxICON_INFORMATION);
}

void MyFrame::RenderBackButton(wxBoxSizer *vbox)
{
    int margin = this->windowSize.GetWidth() * 0.025;

    wxButton *backButton = new wxButton(this, ID_BackButton, wxT("Zurück"));
    backButton->SetBackgroundColour("#0A74DA");
    backButton->SetForegroundColour(*wxWHITE);
    backButton->SetToolTip("Zurück zur Startseite");
    vbox->Add(backButton, 0, wxLEFT | wxBOTTOM | wxTOP, margin);
}

void MyFrame::OnBack(wxCommandEvent &event)
{
    this->DestroyChildren();
    ShowStartView();
    this->currentView = Start;
}

void MyFrame::OnCalculateCommuterBenefit(wxCommandEvent &event)
{
    wxString workingDaysStr = workingDaysInput->GetValue();
    wxString commuteInKmStr = commuteInKmInput->GetValue();

    if (workingDaysStr.IsEmpty() || commuteInKmStr.IsEmpty())
    {
        wxMessageBox("Bitte fülle alle Felder aus.", "Fehler", wxOK | wxICON_ERROR);
        return;
    }

    int workingDays = std::stoi(workingDaysStr.ToStdString());
    int commuteInKm = std::stoi(commuteInKmStr.ToStdString());

    if (workingDays < 0 || commuteInKm < 0)
    {
        wxMessageBox("Bitte gebe nur positive Zahlen ein.", "Fehler", wxOK | wxICON_ERROR);
        return;
    }

    unsigned int workingDaysU = static_cast<unsigned int>(workingDays);
    unsigned int commuteInKmU = static_cast<unsigned int>(commuteInKm);

    CommuterBenefitCalculator calculator(workingDaysU, commuteInKmU);
    double benefit = calculator.calculateBenefit();

    wxString message = wxString::Format("Bei %d Arbeitstagen und einem Arbeitsweg von %dkm beträgt dein Pendlerpauschalenbetrag %.2f€.", workingDays, commuteInKm, benefit);
    wxMessageBox(message, "Ergebnis", wxOK | wxICON_INFORMATION);
    calculator.~CommuterBenefitCalculator();
}

void MyFrame::ShowStartView()
{
    wxPanel *descriptionPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *descBox = new wxBoxSizer(wxHORIZONTAL);

    int margin = this->windowSize.GetWidth() * 0.1;
    descriptionPanel->SetSizer(descBox);

    wxStaticText *description = new wxStaticText(descriptionPanel, wxID_ANY, wxT(""));
    description->SetLabel("Mit dieser Anwendungen können einige Berechnungen im Bereich Finanzen durchgeführt werden. Dieses Projekt wurde im Rahmen meines Bachelor-Studiums erstellt und ist Teil des Moduls C++ Programmierung.\n\nDie Anwendung wurde mit wxWidgets erstellt und ist plattformunabhängig.\n\nBenutzer können verschiedene Rechner verwenden, um verschiedene Berechnungen durchzuführen, die im Finanzbereich häufig vorkommen.\n\nZu diesen Rechnern gehört der Pendlerpauschalenrechner, der Zinsenrechner, der Renditerechner und der Prozentrechner. Diese werden detaillierter auf der jeweiligen Seite erklärt.");
    descBox->Add(description, 1, wxEXPAND | wxLEFT | wxRIGHT, margin);
    description->Wrap(this->windowSize.GetWidth() - 2 * margin);

    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxColour buttonColour("#0A74DA");
    wxFont buttonFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    auto addButton = [panel, vbox, buttonColour, buttonFont](int id, const wxString &label)
    {
        wxButton *button = new wxButton(panel, id, label);
        button->SetBackgroundColour(buttonColour);
        button->SetForegroundColour(*wxWHITE);
        button->SetFont(buttonFont);
        vbox->Add(button, 0, wxEXPAND | wxALL, 10);
    };

    addButton(ID_OpenPendlerpauschaleView, wxT("Pendlerpauschale"));
    addButton(ID_OpenZinsenView, wxT("Zinsenrechner"));
    addButton(ID_OpenRenditeView, wxT("Renditerechner"));
    addButton(ID_OpenProzentView, wxT("Prozentrechner"));

    panel->SetSizer(vbox);

    wxBoxSizer *centerBox = new wxBoxSizer(wxVERTICAL);
    centerBox->Add(descriptionPanel, 0, wxEXPAND | wxALL);
    centerBox->Add(panel, 1, wxALIGN_CENTER);
    SetSizer(centerBox);
    this->Layout();
}

void MyFrame::ShowPendlerpauschaleView()
{
    wxBoxSizer *centerBox = new wxBoxSizer(wxVERTICAL);

    RenderBackButton(centerBox);

    wxPanel *descriptionPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *descBox = new wxBoxSizer(wxHORIZONTAL);

    int margin = this->windowSize.GetWidth() * 0.1;
    descriptionPanel->SetSizer(descBox);

    wxStaticText *description = new wxStaticText(descriptionPanel, wxID_ANY, wxT(""));
    description->SetLabel("Zur Berechnung der Pendlerpauschale werden verschiedene Informationen von dir benötigt. Gebe diese bitte in den folgenden Feldern an. Deine Daten werden nicht gespeichert!");
    descBox->Add(description, 1, wxEXPAND | wxLEFT | wxRIGHT, margin);
    description->Wrap(this->windowSize.GetWidth() - 2 * margin);

    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    /**
     * Start Form
     */
    wxFont boldFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxStaticText *workingDaysLabel = new wxStaticText(panel, wxID_ANY, wxT("Anzahl der Arbeitstage pro Jahr:"));
    vbox->Add(workingDaysLabel, 0, wxEXPAND | wxALL, 10);
    workingDaysLabel->Wrap(this->windowSize.GetWidth() - 2 * margin);
    workingDaysLabel->SetFont(boldFont);

    workingDaysInput = new wxTextCtrl(panel, ID_WorkingDaysInput);
    workingDaysInput->SetHint("z.B. 220");
    workingDaysInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(workingDaysInput, 0, wxEXPAND | wxALL, 10);

    wxStaticText *commuteInKmLabel = new wxStaticText(panel, wxID_ANY, wxT("Entfernung zur Arbeit in Kilometern für eine Strecke:"));
    commuteInKmLabel->SetFont(boldFont);
    vbox->Add(commuteInKmLabel, 0, wxEXPAND | wxALL, 10);

    commuteInKmInput = new wxTextCtrl(panel, ID_CommuteInKmInput);
    commuteInKmInput->SetHint("z.B. 20");
    commuteInKmInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(commuteInKmInput, 0, wxEXPAND | wxALL, 10);

    wxButton *calculateBenefitButton = new wxButton(panel, ID_CalculateBenefitButton, wxT("Berechnen"));
    calculateBenefitButton->SetBackgroundColour("#0A74DA");
    calculateBenefitButton->SetForegroundColour(*wxWHITE);
    calculateBenefitButton->SetFont(boldFont);
    vbox->Add(calculateBenefitButton, 0, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);

    centerBox->Add(descriptionPanel, 0, wxEXPAND | wxALL);
    centerBox->Add(panel, 1, wxALIGN_CENTER);
    SetSizer(centerBox);
    this->Layout();
}

void MyFrame::ShowZinsenView()
{
}

void MyFrame::ShowRenditeView()
{
}

void MyFrame::ShowProzentView()
{
}

void MyFrame::OnOpenPendlerpauschaleView(wxCommandEvent &event)
{
    if (this->currentView != Pendlerpauschale)
    {
        this->DestroyChildren();
        ShowPendlerpauschaleView();
        this->currentView = Pendlerpauschale;
    }
}

void MyFrame::OnOpenZinsenView(wxCommandEvent &event)
{
    if (this->currentView != Zinsen)
    {
        this->DestroyChildren();
        ShowZinsenView();
        this->currentView = Zinsen;
    }
}

void MyFrame::OnOpenRenditeView(wxCommandEvent &event)
{
    if (this->currentView != Rendite)
    {
        this->DestroyChildren();
        ShowRenditeView();
        this->currentView = Rendite;
    }
}

void MyFrame::OnOpenProzentView(wxCommandEvent &event)
{
    if (this->currentView != Prozent)
    {
        this->DestroyChildren();
        ShowProzentView();
        this->currentView = Prozent;
    }
}