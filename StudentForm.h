#pragma once

#include "DataManager.h"
#include "Student.h"
#include "InputDialog.h"
#include "Structures.h"
#include <string>
#include <vector>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Runtime::InteropServices;

namespace LoginGUI {

    public ref struct ManagedCourse {
        String^ title;
        String^ syllabus;
        int creditHours;
        String^ instructor;
        String^ prerequisites;
    };

    public ref struct ManagedGrade {
        String^ Subject;
        int Quiz;
        int Assignment;
        int Midterm;
        int Practical;
        int Final;
        int Total;
        double GPA;
        int ID;
    };

    public ref class StudentForm : public Form
    {
    public:
        StudentForm(DataManager& dataManager, int studentID, String^ username)
            : dm(dataManager), studentID(studentID), username(username)
        {
            InitializeComponent();
            this->DoubleBuffered = true;
        }

    protected:
        ~StudentForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        DataManager& dm;
        int studentID;
        String^ username;
        System::ComponentModel::Container^ components;
        Label^ welcomeLabel;
        Button^ registerCourseButton;
        Button^ findCourseButton;
        Button^ viewGradesButton;
        Button^ viewRegisteredCoursesButton;
        Button^ generateReportButton;
        Button^ filterGradesButton;
        Button^ exitButton;
        DataGridView^ outputGrid;
        TextBox^ filterGpaBox;
        Button^ filterButton;
        Label^ filterLabel;
        PictureBox^ defaultImage; 
        bool isImageVisible; 

        std::string ToStdString(String^ managedString)
        {
            if (String::IsNullOrEmpty(managedString))
                return std::string();

            IntPtr ptr = Marshal::StringToHGlobalAnsi(managedString);
            try {
                return std::string(static_cast<const char*>(ptr.ToPointer()));
            }
            finally {
                Marshal::FreeHGlobal(ptr);
            }
        }

        ManagedCourse^ ToManagedCourse(const Course& nativeCourse)
        {
            ManagedCourse^ managedCourse = gcnew ManagedCourse();
            managedCourse->title = gcnew String(nativeCourse.title.c_str());
            managedCourse->syllabus = gcnew String(nativeCourse.syllabus.c_str());
            managedCourse->creditHours = nativeCourse.creditHours;
            managedCourse->instructor = gcnew String(nativeCourse.instructor.c_str());
            managedCourse->prerequisites = gcnew String(nativeCourse.prerequisites.c_str());
            return managedCourse;
        }

        ManagedGrade^ ToManagedGrade(const Grade& nativeGrade)
        {
            ManagedGrade^ managedGrade = gcnew ManagedGrade();
            managedGrade->Subject = gcnew String(nativeGrade.Subject.c_str());
            managedGrade->Quiz = nativeGrade.Quiz;
            managedGrade->Assignment = nativeGrade.Assignment;
            managedGrade->Midterm = nativeGrade.Midterm;
            managedGrade->Practical = nativeGrade.Practical;
            managedGrade->Final = nativeGrade.Final;
            managedGrade->Total = nativeGrade.Total;
            managedGrade->GPA = nativeGrade.GPA;
            managedGrade->ID = nativeGrade.ID;
            return managedGrade;
        }

        void InitializeComponent(void)
        {
            components = gcnew System::ComponentModel::Container();
            this->Text = "Student Dashboard";
            this->ClientSize = Drawing::Size(800, 500);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->StartPosition = FormStartPosition::CenterScreen;

            welcomeLabel = gcnew Label();
            welcomeLabel->Text = "Welcome, " + username;
            welcomeLabel->Font = gcnew Drawing::Font("Arial", 12, FontStyle::Bold);
            welcomeLabel->ForeColor = Color::White;
            welcomeLabel->BackColor = Color::Transparent;
            welcomeLabel->AutoSize = true;
            welcomeLabel->Location = Point(20, 20);
            welcomeLabel->TextAlign = ContentAlignment::MiddleCenter;

            registerCourseButton = gcnew Button();
            registerCourseButton->Text = "Register for a Course";
            registerCourseButton->Size = Drawing::Size(150, 40);
            registerCourseButton->Location = Point(20, 70);
            registerCourseButton->BackColor = Color::Red;
            registerCourseButton->ForeColor = Color::White;
            registerCourseButton->FlatStyle = FlatStyle::Flat;
            registerCourseButton->FlatAppearance->BorderSize = 0;
            registerCourseButton->Click += gcnew EventHandler(this, &StudentForm::OnRegisterCourseClicked);
            registerCourseButton->MouseEnter += gcnew EventHandler(this, &StudentForm::OnButtonHover);
            registerCourseButton->MouseLeave += gcnew EventHandler(this, &StudentForm::OnButtonLeave);

            findCourseButton = gcnew Button();
            findCourseButton->Text = "Find a Course";
            findCourseButton->Size = Drawing::Size(150, 40);
            findCourseButton->Location = Point(20, 120);
            findCourseButton->BackColor = Color::Red;
            findCourseButton->ForeColor = Color::White;
            findCourseButton->FlatStyle = FlatStyle::Flat;
            findCourseButton->FlatAppearance->BorderSize = 0;
            findCourseButton->Click += gcnew EventHandler(this, &StudentForm::OnFindCourseClicked);
            findCourseButton->MouseEnter += gcnew EventHandler(this, &StudentForm::OnButtonHover);
            findCourseButton->MouseLeave += gcnew EventHandler(this, &StudentForm::OnButtonLeave);

            viewGradesButton = gcnew Button();
            viewGradesButton->Text = "View Grades";
            viewGradesButton->Size = Drawing::Size(150, 40);
            viewGradesButton->Location = Point(20, 170);
            viewGradesButton->BackColor = Color::Red;
            viewGradesButton->ForeColor = Color::White;
            viewGradesButton->FlatStyle = FlatStyle::Flat;
            viewGradesButton->FlatAppearance->BorderSize = 0;
            viewGradesButton->Click += gcnew EventHandler(this, &StudentForm::OnViewGradesClicked);
            viewGradesButton->MouseEnter += gcnew EventHandler(this, &StudentForm::OnButtonHover);
            viewGradesButton->MouseLeave += gcnew EventHandler(this, &StudentForm::OnButtonLeave);

            viewRegisteredCoursesButton = gcnew Button();
            viewRegisteredCoursesButton->Text = "View Registered Courses";
            viewRegisteredCoursesButton->Size = Drawing::Size(150, 40);
            viewRegisteredCoursesButton->Location = Point(20, 220);
            viewRegisteredCoursesButton->BackColor = Color::Red;
            viewRegisteredCoursesButton->ForeColor = Color::White;
            viewRegisteredCoursesButton->FlatStyle = FlatStyle::Flat;
            viewRegisteredCoursesButton->FlatAppearance->BorderSize = 0;
            viewRegisteredCoursesButton->Click += gcnew EventHandler(this, &StudentForm::OnViewRegisteredCoursesClicked);
            viewRegisteredCoursesButton->MouseEnter += gcnew EventHandler(this, &StudentForm::OnButtonHover);
            viewRegisteredCoursesButton->MouseLeave += gcnew EventHandler(this, &StudentForm::OnButtonLeave);

            generateReportButton = gcnew Button();
            generateReportButton->Text = "Generate Report";
            generateReportButton->Size = Drawing::Size(150, 40);
            generateReportButton->Location = Point(20, 270);
            generateReportButton->BackColor = Color::Red;
            generateReportButton->ForeColor = Color::White;
            generateReportButton->FlatStyle = FlatStyle::Flat;
            generateReportButton->FlatAppearance->BorderSize = 0;
            generateReportButton->Click += gcnew EventHandler(this, &StudentForm::OnGenerateReportClicked);
            generateReportButton->MouseEnter += gcnew EventHandler(this, &StudentForm::OnButtonHover);
            generateReportButton->MouseLeave += gcnew EventHandler(this, &StudentForm::OnButtonLeave);

            filterGradesButton = gcnew Button();
            filterGradesButton->Text = "Filter Grades";
            filterGradesButton->Size = Drawing::Size(150, 40);
            filterGradesButton->Location = Point(20, 320);
            filterGradesButton->BackColor = Color::Red;
            filterGradesButton->ForeColor = Color::White;
            filterGradesButton->FlatStyle = FlatStyle::Flat;
            filterGradesButton->FlatAppearance->BorderSize = 0;
            filterGradesButton->Click += gcnew EventHandler(this, &StudentForm::OnFilterGradesClicked);
            filterGradesButton->MouseEnter += gcnew EventHandler(this, &StudentForm::OnButtonHover);
            filterGradesButton->MouseLeave += gcnew EventHandler(this, &StudentForm::OnButtonLeave);

            exitButton = gcnew Button();
            exitButton->Text = "Exit";
            exitButton->Size = Drawing::Size(150, 40);
            exitButton->Location = Point(20, 370);
            exitButton->BackColor = Color::Red;
            exitButton->ForeColor = Color::White;
            exitButton->FlatStyle = FlatStyle::Flat;
            exitButton->FlatAppearance->BorderSize = 0;
            exitButton->Click += gcnew EventHandler(this, &StudentForm::OnExitClicked);
            exitButton->MouseEnter += gcnew EventHandler(this, &StudentForm::OnButtonHover);
            exitButton->MouseLeave += gcnew EventHandler(this, &StudentForm::OnButtonLeave);

            outputGrid = gcnew DataGridView();
            outputGrid->Location = Point(200, 70);
            outputGrid->Size = Drawing::Size(570, 400);
            outputGrid->ReadOnly = true;
            outputGrid->AllowUserToAddRows = false;
            outputGrid->RowHeadersVisible = false;
            outputGrid->BackgroundColor = Color::White;
            outputGrid->BorderStyle = BorderStyle::None;
            outputGrid->GridColor = Color::LightGray;
            outputGrid->DefaultCellStyle->Font = gcnew Drawing::Font("Arial", 10);
            outputGrid->DefaultCellStyle->BackColor = Color::White;
            outputGrid->DefaultCellStyle->ForeColor = Color::Black;
            outputGrid->DefaultCellStyle->SelectionBackColor = Color::LightBlue;
            outputGrid->DefaultCellStyle->SelectionForeColor = Color::Black;
            outputGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(147, 112, 219);
            outputGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            outputGrid->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font("Arial", 10, FontStyle::Bold);
            outputGrid->EnableHeadersVisualStyles = false;
            outputGrid->Visible = false; // إخفاء في البداية

            defaultImage = gcnew PictureBox();
            defaultImage->Location = Point(200, 70);
            defaultImage->Size = Drawing::Size(570, 400);
            defaultImage->SizeMode = PictureBoxSizeMode::StretchImage;
            try {
                defaultImage->Image = Image::FromFile("ASU.jpeg");
            }
            catch (Exception^ ex) {
                MessageBox::Show("Failed to load default image: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                defaultImage->Image = nullptr;
            }
            defaultImage->Visible = true;
            isImageVisible = true;

            filterLabel = gcnew Label();
            filterLabel->Text = "Enter Minimum GPA:";
            filterLabel->Font = gcnew Drawing::Font("Arial", 12, FontStyle::Bold);
            filterLabel->ForeColor = Color::White;
            filterLabel->BackColor = Color::Transparent;
            filterLabel->AutoSize = true;
            filterLabel->Location = Point(200, 20);
            filterLabel->Visible = false;

            filterGpaBox = gcnew TextBox();
            filterGpaBox->Location = Point(380, 20);
            filterGpaBox->Size = Drawing::Size(100, 30);
            filterGpaBox->BackColor = Color::White;
            filterGpaBox->ForeColor = Color::Black;
            filterGpaBox->Visible = false;

            filterButton = gcnew Button();
            filterButton->Text = "Filter";
            filterButton->Size = Drawing::Size(80, 30);
            filterButton->Location = Point(490, 20);
            filterButton->BackColor = Color::Red;
            filterButton->ForeColor = Color::White;
            filterButton->FlatStyle = FlatStyle::Flat;
            filterButton->FlatAppearance->BorderSize = 0;
            filterButton->Click += gcnew EventHandler(this, &StudentForm::OnFilterButtonClicked);
            filterButton->MouseEnter += gcnew EventHandler(this, &StudentForm::OnButtonHover);
            filterButton->MouseLeave += gcnew EventHandler(this, &StudentForm::OnButtonLeave);
            filterButton->Visible = false;

            this->Controls->Add(welcomeLabel);
            this->Controls->Add(registerCourseButton);
            this->Controls->Add(findCourseButton);
            this->Controls->Add(viewGradesButton);
            this->Controls->Add(viewRegisteredCoursesButton);
            this->Controls->Add(generateReportButton);
            this->Controls->Add(filterGradesButton);
            this->Controls->Add(exitButton);
            this->Controls->Add(outputGrid);
            this->Controls->Add(filterLabel);
            this->Controls->Add(filterGpaBox);
            this->Controls->Add(filterButton);
            this->Controls->Add(defaultImage);
        }

    protected:
        virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override
        {
            int width = this->ClientSize.Width;
            int height = this->ClientSize.Height;
            System::Drawing::Rectangle leftRect(0, 0, 190, height);
            System::Drawing::Rectangle rightRect(190, 0, width - 190, height);
            System::Drawing::Drawing2D::LinearGradientBrush^ leftBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(leftRect, Color::DarkGray, Color::White, System::Drawing::Drawing2D::LinearGradientMode::Vertical);
            System::Drawing::Drawing2D::LinearGradientBrush^ rightBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(rightRect, Color::White, Color::DarkGray, System::Drawing::Drawing2D::LinearGradientMode::Vertical);
            e->Graphics->FillRectangle(leftBrush, leftRect);
            e->Graphics->FillRectangle(rightBrush, rightRect);
        }

    private:
        void OnButtonHover(Object^ sender, EventArgs^ e)
        {
            Button^ btn = safe_cast<Button^>(sender);
            btn->BackColor = Color::DarkRed;
        }

        void OnButtonLeave(Object^ sender, EventArgs^ e)
        {
            Button^ btn = safe_cast<Button^>(sender);
            btn->BackColor = Color::Red;
        }

        void OnRegisterCourseClicked(Object^ sender, EventArgs^ e)
        {
            try {
                defaultImage->Visible = false;
                isImageVisible = false;
                outputGrid->Visible = true;

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();

                outputGrid->Columns->Add("Title", "Title");
                outputGrid->Columns->Add("Syllabus", "Syllabus");
                outputGrid->Columns->Add("CreditHours", "Credit Hours");
                outputGrid->Columns->Add("Instructor", "Instructor");
                outputGrid->Columns->Add("Prerequisites", "Prerequisites");
                DataGridViewButtonColumn^ registerColumn = gcnew DataGridViewButtonColumn();
                registerColumn->Name = "Register";
                registerColumn->Text = "Register";
                registerColumn->UseColumnTextForButtonValue = true;
                outputGrid->Columns->Add(registerColumn);

                for (const auto& course : dm.courses) {
                    ManagedCourse^ managedCourse = ToManagedCourse(course);
                    array<Object^>^ row = {
                        managedCourse->title,
                        managedCourse->syllabus,
                        managedCourse->creditHours.ToString(),
                        managedCourse->instructor,
                        String::IsNullOrEmpty(managedCourse->prerequisites) ? "None" : managedCourse->prerequisites,
                        "Register"
                    };
                    outputGrid->Rows->Add(row);
                }

                for each(DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 100;
                }
                outputGrid->CellClick += gcnew DataGridViewCellEventHandler(this, &StudentForm::OnRegisterCellClick);
                filterLabel->Visible = false;
                filterGpaBox->Visible = false;
                filterButton->Visible = false;
            }
            catch (const std::exception& ex) {
                MessageBox::Show("An error occurred: " + gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnRegisterCellClick(Object^ sender, DataGridViewCellEventArgs^ e)
        {
            if (e->ColumnIndex == outputGrid->Columns["Register"]->Index && e->RowIndex >= 0) {
                String^ courseName = safe_cast<String^>(outputGrid->Rows[e->RowIndex]->Cells["Title"]->Value);
                try {
                    Student student(dm);
                    student.setStudentID(studentID);
                    if (username != nullptr) {
                        student.setUsername(ToStdString(username));
                    }

                    std::string stdCourseName = ToStdString(courseName);
                    std::string errorMessage;
                    bool success = student.registerCourse(stdCourseName, errorMessage);

                    MessageBox::Show(gcnew String(errorMessage.c_str()), success ? "Success" : "Error",
                        MessageBoxButtons::OK, success ? MessageBoxIcon::Information : MessageBoxIcon::Error);
                }
                catch (const std::exception& ex) {
                    MessageBox::Show("An error occurred: " + gcnew String(ex.what()), "Error",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void OnFindCourseClicked(Object^ sender, EventArgs^ e)
        {
            InputDialog^ dialog = gcnew InputDialog("Enter course name to find:", "Find Course");
            if (dialog->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            String^ searchName = dialog->inputBox->Text;
            if (String::IsNullOrEmpty(searchName)) {
                MessageBox::Show("Course name cannot be empty.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try {
                defaultImage->Visible = false;
                isImageVisible = false;
                outputGrid->Visible = true;

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();

                outputGrid->Columns->Add("Title", "Title");
                outputGrid->Columns->Add("Syllabus", "Syllabus");
                outputGrid->Columns->Add("CreditHours", "Credit Hours");
                outputGrid->Columns->Add("Instructor", "Instructor");
                outputGrid->Columns->Add("Prerequisites", "Prerequisites");

                Student student(dm);
                student.setStudentID(studentID);
                if (username != nullptr) {
                    student.setUsername(ToStdString(username));
                }

                std::string stdSearchName = ToStdString(searchName);
                Course nativeCourse = student.findCourse(stdSearchName);
                ManagedCourse^ course = ToManagedCourse(nativeCourse);

                if (String::IsNullOrEmpty(course->title)) {
                    MessageBox::Show("Course not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
                else {
                    array<Object^>^ row = {
                        course->title,
                        course->syllabus,
                        course->creditHours.ToString(),
                        course->instructor,
                        String::IsNullOrEmpty(course->prerequisites) ? "None" : course->prerequisites
                    };
                    outputGrid->Rows->Add(row);
                }

                for each(DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 110;
                }
                filterLabel->Visible = false;
                filterGpaBox->Visible = false;
                filterButton->Visible = false;
            }
            catch (const std::exception& ex) {
                MessageBox::Show("An error occurred: " + gcnew String(ex.what()), "Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnViewGradesClicked(Object^ sender, EventArgs^ e)
        {
            try {
                defaultImage->Visible = false;
                isImageVisible = false;
                outputGrid->Visible = true;

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();

                outputGrid->Columns->Add("Subject", "Subject");
                outputGrid->Columns->Add("Quiz", "Quiz");
                outputGrid->Columns->Add("Assignment", "Assignment");
                outputGrid->Columns->Add("Midterm", "Midterm");
                outputGrid->Columns->Add("Practical", "Practical");
                outputGrid->Columns->Add("Final", "Final");
                outputGrid->Columns->Add("Total", "Total");
                outputGrid->Columns->Add("GPA", "GPA");

                Student student(dm);
                student.setStudentID(studentID);
                if (username != nullptr) {
                    student.setUsername(ToStdString(username));
                }

                std::vector<Grade> nativeGrades = student.getGrades();
                if (nativeGrades.empty()) {
                    MessageBox::Show("No grades found for this student!", "Grades", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return;
                }

                for (const auto& nativeGrade : nativeGrades) {
                    ManagedGrade^ grade = ToManagedGrade(nativeGrade);
                    array<Object^>^ row = {
                        grade->Subject,
                        grade->Quiz.ToString(),
                        grade->Assignment.ToString(),
                        grade->Midterm.ToString(),
                        grade->Practical.ToString(),
                        grade->Final.ToString(),
                        grade->Total.ToString(),
                        grade->GPA.ToString("F2")
                    };
                    outputGrid->Rows->Add(row);
                }

                for each(DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 70;
                }
                filterLabel->Visible = false;
                filterGpaBox->Visible = false;
                filterButton->Visible = false;
            }
            catch (const std::exception& ex) {
                MessageBox::Show("An error occurred: " + gcnew String(ex.what()), "Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnViewRegisteredCoursesClicked(Object^ sender, EventArgs^ e)
        {
            try {
                defaultImage->Visible = false;
                isImageVisible = false;
                outputGrid->Visible = true;

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();

                outputGrid->Columns->Add("Course", "Registered Courses");

                Student student(dm);
                student.setStudentID(studentID);
                if (username != nullptr) {
                    student.setUsername(ToStdString(username));
                }

                std::vector<std::string> courses = student.getRegisteredCourses();
                if (courses.empty()) {
                    MessageBox::Show("No registration data found for this student.", "Registered Courses",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return;
                }

                for (const auto& course : courses) {
                    array<Object^>^ row = { gcnew String(course.c_str()) };
                    outputGrid->Rows->Add(row);
                }

                outputGrid->Columns[0]->Width = 550;
                filterLabel->Visible = false;
                filterGpaBox->Visible = false;
                filterButton->Visible = false;
            }
            catch (const std::exception& ex) {
                MessageBox::Show("An error occurred: " + gcnew String(ex.what()), "Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnGenerateReportClicked(Object^ sender, EventArgs^ e)
        {
            try {
                defaultImage->Visible = false;
                isImageVisible = false;
                outputGrid->Visible = true;

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();

                outputGrid->Columns->Add("Report", "Student Report");

                Student student(dm);
                student.setStudentID(studentID);
                if (username != nullptr) {
                    student.setUsername(ToStdString(username));
                }

                std::string report = student.generateReport(std::to_string(studentID));
                array<Object^>^ row = { gcnew String(report.c_str()) };
                outputGrid->Rows->Add(row);

                outputGrid->Columns[0]->Width = 550;
                filterLabel->Visible = false;
                filterGpaBox->Visible = false;
                filterButton->Visible = false;
            }
            catch (const std::exception& ex) {
                MessageBox::Show("An error occurred: " + gcnew String(ex.what()), "Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnFilterGradesClicked(Object^ sender, EventArgs^ e)
        {
            try {
                defaultImage->Visible = false;
                isImageVisible = false;
                outputGrid->Visible = true;

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();

                outputGrid->Columns->Add("Subject", "Subject");
                outputGrid->Columns->Add("Quiz", "Quiz");
                outputGrid->Columns->Add("Assignment", "Assignment");
                outputGrid->Columns->Add("Midterm", "Midterm");
                outputGrid->Columns->Add("Practical", "Practical");
                outputGrid->Columns->Add("Final", "Final");
                outputGrid->Columns->Add("Total", "Total");
                outputGrid->Columns->Add("GPA", "GPA");

                Student student(dm);
                student.setStudentID(studentID);
                if (username != nullptr) {
                    student.setUsername(ToStdString(username));
                }

                std::vector<Grade> nativeGrades = student.getGrades();
                if (nativeGrades.empty()) {
                    MessageBox::Show("No grades found for this student!", "Grades", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return;
                }

                for (const auto& nativeGrade : nativeGrades) {
                    ManagedGrade^ grade = ToManagedGrade(nativeGrade);
                    array<Object^>^ row = {
                        grade->Subject,
                        grade->Quiz.ToString(),
                        grade->Assignment.ToString(),
                        grade->Midterm.ToString(),
                        grade->Practical.ToString(),
                        grade->Final.ToString(),
                        grade->Total.ToString(),
                        grade->GPA.ToString("F2")
                    };
                    outputGrid->Rows->Add(row);
                }

                for each(DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 70;
                }

                filterLabel->Visible = true;
                filterGpaBox->Visible = true;
                filterButton->Visible = true;
            }
            catch (const std::exception& ex) {
                MessageBox::Show("An error occurred: " + gcnew String(ex.what()), "Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnFilterButtonClicked(Object^ sender, EventArgs^ e)
        {
            String^ input = filterGpaBox->Text;
            if (String::IsNullOrEmpty(input)) {
                MessageBox::Show("GPA value cannot be empty.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try {
                double minGPA = Double::Parse(input);
                Student student(dm);
                student.setStudentID(studentID);
                if (username != nullptr) {
                    student.setUsername(ToStdString(username));
                }

                std::vector<Grade> nativeGrades = student.filterGrades(minGPA);
                outputGrid->Rows->Clear();

                if (nativeGrades.empty()) {
                    MessageBox::Show("No grades found with GPA >= " + minGPA.ToString("F2"), "Filtered Grades",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return;
                }

                for (const auto& nativeGrade : nativeGrades) {
                    ManagedGrade^ grade = ToManagedGrade(nativeGrade);
                    array<Object^>^ row = {
                        grade->Subject,
                        grade->Quiz.ToString(),
                        grade->Assignment.ToString(),
                        grade->Midterm.ToString(),
                        grade->Practical.ToString(),
                        grade->Final.ToString(),
                        grade->Total.ToString(),
                        grade->GPA.ToString("F2")
                    };
                    outputGrid->Rows->Add(row);
                }
            }
            catch (Exception^) {
                MessageBox::Show("Invalid GPA value.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            catch (const std::exception& ex) {
                MessageBox::Show("An error occurred: " + gcnew String(ex.what()), "Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnExitClicked(Object^ sender, EventArgs^ e)
        {
            if (MessageBox::Show("Are you sure you want to exit?", "Confirm", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
                this->Close();
            }
            else {
                defaultImage->Visible = true;
                isImageVisible = true;
                outputGrid->Visible = false;
                filterLabel->Visible = false;
                filterGpaBox->Visible = false;
                filterButton->Visible = false;
            }
        }
    };
}