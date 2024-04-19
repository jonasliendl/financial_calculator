// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "./pendlerpauschale/CommuterBenefitCalculator.h"
#include "./yield/Yield.h"
#include "./percentage/PercentageCalculator.h"

enum View
{
    Start,
    Pendlerpauschale,
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
    void OnOpenRenditeView(wxCommandEvent &event);
    void OnOpenProzentView(wxCommandEvent &event);
    void OnCalculateCommuterBenefit(wxCommandEvent &event);
    void OnCalculateYield(wxCommandEvent &event);
    void OnCalculatePercentage(wxCommandEvent &event);
    void ShowStartView();
    void ShowPendlerpauschaleView();
    void ShowRenditeView();
    void ShowProzentView();
    void RenderBackButton(wxBoxSizer *vbox);
    // Window properties
    wxString title;
    wxPoint startPoint;
    wxSize windowSize;
    // Routing
    View currentView;
    // Inputs - CommuterBenefit
    wxTextCtrl *workingDaysInput;
    wxTextCtrl *commuteInKmInput;
    // Inputs - Yield
    wxTextCtrl *startValueInput;
    wxTextCtrl *endValueInput;
    wxTextCtrl *startYearInput;
    wxTextCtrl *endYearInput;
    // Inputs - Percentage
    wxTextCtrl *percentStartValueInput;
    wxTextCtrl *percentEndValueInput;
    wxTextCtrl *percentInterestRateInput;
    wxDECLARE_EVENT_TABLE();
};
enum
{
    ID_Hello = 1,
    ID_OpenPendlerpauschaleView = 2,
    ID_OpenRenditeView = 4,
    ID_OpenProzentView = 5,
    ID_WorkingDaysInput = 6,
    ID_CommuteInKmInput = 7,
    ID_CalculateBenefitButton = 8,
    ID_BackButton = 9,
    ID_StartValueInput = 10,
    ID_EndValueInput = 11,
    ID_StartYearInput = 12,
    ID_EndYearInput = 13,
    ID_CalculateYieldButton = 14,
    ID_StartValuePercentageInput = 15,
    ID_EndValuePercentageInput = 16,
    ID_InterestRatePercentageInput = 17,
    ID_CalculatePercentageButton = 18
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
        EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
            EVT_BUTTON(ID_OpenPendlerpauschaleView, MyFrame::OnOpenPendlerpauschaleView)
                EVT_BUTTON(ID_OpenRenditeView, MyFrame::OnOpenRenditeView)
                    EVT_BUTTON(ID_OpenProzentView, MyFrame::OnOpenProzentView)
                        EVT_BUTTON(ID_BackButton, MyFrame::OnBack)
                            EVT_BUTTON(ID_CalculateBenefitButton, MyFrame::OnCalculateCommuterBenefit)
                                EVT_BUTTON(ID_CalculateYieldButton, MyFrame::OnCalculateYield)
                                    EVT_BUTTON(ID_CalculatePercentageButton, MyFrame::OnCalculatePercentage)
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

    // TODO: Add text to explain calculation and context

    centerBox->Add(descriptionPanel, 0, wxEXPAND | wxALL);
    centerBox->Add(panel, 1, wxALIGN_CENTER);
    SetSizer(centerBox);
    this->Layout();
}

void MyFrame::OnCalculateYield(wxCommandEvent &event)
{
    wxString startValueStr = startValueInput->GetValue();
    wxString endValueStr = endValueInput->GetValue();
    wxString startYearStr = startYearInput->GetValue();
    wxString endYearStr = endYearInput->GetValue();

    if (startValueStr.IsEmpty() || endValueStr.IsEmpty() || startYearStr.IsEmpty() || endYearStr.IsEmpty())
    {
        wxMessageBox("Bitte fülle alle Felder aus.", "Fehler", wxOK | wxICON_ERROR);
        return;
    }

    float startValue = std::stof(startValueStr.ToStdString());
    float endValue = std::stof(endValueStr.ToStdString());
    int startYear = std::stoi(startYearStr.ToStdString());
    int endYear = std::stoi(endYearStr.ToStdString());

    if (startValue < 0 || endValue < 0 || startYear < 0 || endYear < 0)
    {
        wxMessageBox("Bitte gebe nur positive Zahlen ein.", "Fehler", wxOK | wxICON_ERROR);
        return;
    }

    Yield yield(startValue, endValue, startYear, endYear);
    yield.calculate();

    double yieldOverall = yield.getYieldOverall();
    double yieldPerAnno = yield.getYieldPerAnno();

    wxString message = wxString::Format("Bei einem Startwert von %.2f€ und einem Endwert von %.2f€ zwischen den Jahren %d und %d beträgt die Rendite %.2f Prozent insgesamt und %.2f Prozent pro Jahr.", startValue, endValue, startYear, endYear, yieldOverall * 100, yieldPerAnno * 100);
    wxMessageBox(message, "Ergebnis", wxOK | wxICON_INFORMATION);
}

void MyFrame::ShowRenditeView()
{
    wxBoxSizer *centerBox = new wxBoxSizer(wxVERTICAL);

    RenderBackButton(centerBox);

    int margin = this->windowSize.GetWidth() * 0.1;

    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    /**
     * Start Form
     */
    wxFont boldFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxStaticText *startValueLabel = new wxStaticText(panel, wxID_ANY, wxT("Startwert in Euro:"));
    vbox->Add(startValueLabel, 0, wxEXPAND | wxALL, 10);
    startValueLabel->Wrap(this->windowSize.GetWidth() - 2 * margin);
    startValueLabel->SetFont(boldFont);

    startValueInput = new wxTextCtrl(panel, ID_StartValueInput);
    startValueInput->SetHint("z.B. 2000");
    startValueInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(startValueInput, 0, wxEXPAND | wxALL, 10);

    wxStaticText *endValueLabel = new wxStaticText(panel, wxID_ANY, wxT("Endwert in Euro:"));
    endValueLabel->SetFont(boldFont);
    vbox->Add(endValueLabel, 0, wxEXPAND | wxALL, 10);

    endValueInput = new wxTextCtrl(panel, ID_EndValueInput);
    endValueInput->SetHint("z.B. 4000");
    endValueInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(endValueInput, 0, wxEXPAND | wxALL, 10);

    wxStaticText *startYearLabel = new wxStaticText(panel, wxID_ANY, wxT("Startjahr:"));
    startYearLabel->SetFont(boldFont);
    vbox->Add(startYearLabel, 0, wxEXPAND | wxALL, 10);

    startYearInput = new wxTextCtrl(panel, ID_StartYearInput);
    startYearInput->SetHint("z.B. 2020");
    startYearInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(startYearInput, 0, wxEXPAND | wxALL, 10);

    wxStaticText *endYearLabel = new wxStaticText(panel, wxID_ANY, wxT("Endjahr:"));
    endYearLabel->SetFont(boldFont);
    vbox->Add(endYearLabel, 0, wxEXPAND | wxALL, 10);

    endYearInput = new wxTextCtrl(panel, ID_EndYearInput);
    endYearInput->SetHint("z.B. 2025");
    endYearInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(endYearInput, 0, wxEXPAND | wxALL, 10);

    wxButton *calculateYield = new wxButton(panel, ID_CalculateYieldButton, wxT("Berechnen"));
    calculateYield->SetBackgroundColour("#0A74DA");
    calculateYield->SetForegroundColour(*wxWHITE);
    calculateYield->SetFont(boldFont);
    vbox->Add(calculateYield, 0, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);

    // TODO: Add text to explain calculation and context

    centerBox->Add(panel, 1, wxALIGN_CENTER);
    SetSizer(centerBox);
    this->Layout();
}

void MyFrame::OnCalculatePercentage(wxCommandEvent &event)
{
    wxString startValueStr = percentStartValueInput->GetValue();
    wxString endValueStr = percentEndValueInput->GetValue();
    wxString interestRateStr = percentInterestRateInput->GetValue();

    if ((startValueStr.IsEmpty() && endValueStr.IsEmpty()) || (interestRateStr.IsEmpty() && endValueStr.IsEmpty()) || (startValueStr.IsEmpty() && interestRateStr.IsEmpty()))
    {
        wxMessageBox("Bitte fülle zwei Felder aus.", "Fehler", wxOK | wxICON_ERROR);
        return;
    }

    double startValue = 0.0;
    double endValue = 0.0;
    double interestRate = 0.0;

    if (!startValueStr.IsEmpty())
    {
        startValue = std::stod(startValueStr.ToStdString());
    }

    if (!endValueStr.IsEmpty())
    {
        endValue = std::stod(endValueStr.ToStdString());
    }

    if (!interestRateStr.IsEmpty())
    {
        interestRate = std::stod(interestRateStr.ToStdString());
    }

    if (startValue < 0 || endValue < 0 || interestRate < 0)
    {
        wxMessageBox("Bitte gebe nur positive Zahlen ein.", "Fehler", wxOK | wxICON_ERROR);
        return;
    }

    PercentageCalculator calculator;
    calculator.changeStartValue(startValue);
    calculator.changeEndValue(endValue);
    calculator.changeInterestRate(interestRate);

    try
    {
        double value = 0.0;
        wxString message;
        if (startValueStr.IsEmpty())
        {
            value = calculator.calculateStartValue();
            message = wxString::Format("Der berechnete Startwert beträgt %.2f€.", value);
        }
        else if (endValueStr.IsEmpty())
        {
            value = calculator.calculateEndValue();
            message = wxString::Format("Der berechnete Endwert beträgt %.2f€.", value);
        }
        else
        {
            value = calculator.calculateInterestRate();
            message = wxString::Format("Der berechnete Zinssatz beträgt %.2f%%.", value * 100);
        }

        wxMessageBox(message, "Ergebnis", wxOK | wxICON_INFORMATION);
        return;
    }
    catch (const std::exception &e)
    {
        wxString message = wxString::Format("Ein Fehler ist aufgetreten: %s", e.what());
        wxMessageBox(message, "Fehler", wxOK | wxICON_ERROR);
        return;
    }
}

void MyFrame::ShowProzentView()
{
    wxBoxSizer *centerBox = new wxBoxSizer(wxVERTICAL);

    RenderBackButton(centerBox);

    wxPanel *descriptionPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *descBox = new wxBoxSizer(wxHORIZONTAL);

    int margin = this->windowSize.GetWidth() * 0.1;
    descriptionPanel->SetSizer(descBox);

    wxStaticText *description = new wxStaticText(descriptionPanel, wxID_ANY, wxT(""));
    description->SetLabel("Fülle zwei der drei Felder aus, um das leere Feld zu berechnen.");
    descBox->Add(description, 1, wxEXPAND | wxLEFT | wxRIGHT, margin);
    description->Wrap(this->windowSize.GetWidth() - 2 * margin);

    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    /**
     * Start Form
     */
    wxFont boldFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxStaticText *startValueLabel = new wxStaticText(panel, wxID_ANY, wxT("Startwert:"));
    vbox->Add(startValueLabel, 0, wxEXPAND | wxALL, 10);
    startValueLabel->Wrap(this->windowSize.GetWidth() - 2 * margin);
    startValueLabel->SetFont(boldFont);

    percentStartValueInput = new wxTextCtrl(panel, ID_StartValuePercentageInput);
    percentStartValueInput->SetHint("z.B. 200");
    percentStartValueInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(percentStartValueInput, 0, wxEXPAND | wxALL, 10);

    wxStaticText *endValueLabel = new wxStaticText(panel, wxID_ANY, wxT("Endwert:"));
    endValueLabel->SetFont(boldFont);
    vbox->Add(endValueLabel, 0, wxEXPAND | wxALL, 10);

    percentEndValueInput = new wxTextCtrl(panel, ID_EndValuePercentageInput);
    percentEndValueInput->SetHint("z.B. 400");
    percentEndValueInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(percentEndValueInput, 0, wxEXPAND | wxALL, 10);

    wxStaticText *interestRateLabel = new wxStaticText(panel, wxID_ANY, wxT("Zinssatz:"));
    interestRateLabel->SetFont(boldFont);
    vbox->Add(interestRateLabel, 0, wxEXPAND | wxALL, 10);

    percentInterestRateInput = new wxTextCtrl(panel, ID_InterestRatePercentageInput);
    percentInterestRateInput->SetHint("z.B. 5.0");
    percentInterestRateInput->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
    vbox->Add(percentInterestRateInput, 0, wxEXPAND | wxALL, 10);

    wxButton *calculatePercentageButton = new wxButton(panel, ID_CalculatePercentageButton, wxT("Berechnen"));
    calculatePercentageButton->SetBackgroundColour("#0A74DA");
    calculatePercentageButton->SetForegroundColour(*wxWHITE);
    calculatePercentageButton->SetFont(boldFont);
    vbox->Add(calculatePercentageButton, 0, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);

    // TODO: Add text to explain calculation and context

    centerBox->Add(descriptionPanel, 0, wxEXPAND | wxALL);
    centerBox->Add(panel, 1, wxALIGN_CENTER);
    SetSizer(centerBox);
    this->Layout();
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