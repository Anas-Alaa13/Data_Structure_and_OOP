#pragma once
#include <fstream>
#include <sstream>
#include "DataManager.h"
#include "Admin.h"
#include "Structures.h"
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <msclr/marshal.h>

namespace LoginGUI {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;
    using namespace System::Runtime::InteropServices;
    using namespace System::Collections::Generic;
    struct UsernameFinder
    {
        std::string targetUsername;
        UsernameFinder(const std::string& username) : targetUsername(username) {}
        bool operator()(const User& u) const
        {
            return u.Username == targetUsername;
        }
    };
    public ref class AdminForm : public Form
    {
    public:
        AdminForm(DataManager& dataManager) : dm(dataManager)
        {
            admin = new Admin(dm);
            InitializeComponent();
            this->DoubleBuffered = true;
        }

        ~AdminForm()
        {
            delete admin;
            if (components)
            {
                delete components;
            }
        }

    private:
        DataManager& dm;
        Admin* admin;
        System::ComponentModel::Container^ components;
        Button^ uploadCourseButton;
        Button^ setPrerequisitesButton;
        Button^ editStudentDataButton;
        Button^ showCoursesButton;
        Button^ manageGradesButton;
        Button^ deleteUserButton;
        Button^ exitButton;
        DataGridView^ outputGrid;
        Panel^ inputPanel;

        TextBox^ titleBox;
        TextBox^ syllabusBox;
        TextBox^ creditHoursBox;
        TextBox^ instructorBox;
        TextBox^ prereqBox;
        TextBox^ usernameBox;
        TextBox^ idBox;
        TextBox^ firstNameBox;
        TextBox^ lastNameBox;
        TextBox^ phoneBox;
        TextBox^ emailBox;
        TextBox^ passwordBox;
        TextBox^ subjectBox;
        TextBox^ quizBox;
        TextBox^ assignmentBox;
        TextBox^ midtermBox;
        TextBox^ practicalBox;
        TextBox^ finalBox;

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

        ref struct ManagedCourse {
            String^ title;
            String^ syllabus;
            int creditHours;
            String^ instructor;
            String^ prerequisites;
        };

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

        ref struct ManagedUser {
            String^ username;
            int id;
            String^ firstName;
            String^ lastName;
            String^ phone;
            String^ email;
            String^ password;
        };

        ManagedUser^ ToManagedUser(const User& nativeUser)
        {
            ManagedUser^ managedUser = gcnew ManagedUser();
            managedUser->username = gcnew String(nativeUser.Username.c_str());
            managedUser->id = nativeUser.ID;
            managedUser->firstName = gcnew String(nativeUser.FirstName.c_str());
            managedUser->lastName = gcnew String(nativeUser.LastName.c_str());
            managedUser->phone = gcnew String(nativeUser.PhoneNumber.c_str());
            managedUser->email = gcnew String(nativeUser.Email.c_str());
            managedUser->password = gcnew String(nativeUser.Password.c_str());
            return managedUser;
        }

        ref struct ManagedStudentGrade {
            String^ subject;
            int quiz;
            int assignment;
            int midterm;
            int practical;
            int finalExam;
        };

        ManagedStudentGrade^ ToManagedStudentGrade(const std::string& subject, int quiz, int assignment, int midterm, int practical, int finalExam)
        {
            ManagedStudentGrade^ grade = gcnew ManagedStudentGrade();
            grade->subject = gcnew String(subject.c_str());
            grade->quiz = quiz;
            grade->assignment = assignment;
            grade->midterm = midterm;
            grade->practical = practical;
            grade->finalExam = finalExam;
            return grade;
        }

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Text = "Admin Dashboard";
            this->ClientSize = Drawing::Size(800, 600);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->StartPosition = FormStartPosition::CenterScreen;

            uploadCourseButton = gcnew Button();
            uploadCourseButton->Text = "Upload Course";
            uploadCourseButton->Location = Point(20, 20);
            uploadCourseButton->Size = Drawing::Size(150, 40);
            uploadCourseButton->BackColor = Color::Red;
            uploadCourseButton->ForeColor = Color::White;
            uploadCourseButton->FlatStyle = FlatStyle::Flat;
            uploadCourseButton->FlatAppearance->BorderSize = 0;
            uploadCourseButton->Click += gcnew EventHandler(this, &AdminForm::OnUploadCourseClicked);
            uploadCourseButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            uploadCourseButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            setPrerequisitesButton = gcnew Button();
            setPrerequisitesButton->Text = "Set Prerequisites";
            setPrerequisitesButton->Location = Point(20, 70);
            setPrerequisitesButton->Size = Drawing::Size(150, 40);
            setPrerequisitesButton->BackColor = Color::Red;
            setPrerequisitesButton->ForeColor = Color::White;
            setPrerequisitesButton->FlatStyle = FlatStyle::Flat;
            setPrerequisitesButton->FlatAppearance->BorderSize = 0;
            setPrerequisitesButton->Click += gcnew EventHandler(this, &AdminForm::OnSetPrerequisitesClicked);
            setPrerequisitesButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            setPrerequisitesButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            editStudentDataButton = gcnew Button();
            editStudentDataButton->Text = "Edit Student Data";
            editStudentDataButton->Location = Point(20, 120);
            editStudentDataButton->Size = Drawing::Size(150, 40);
            editStudentDataButton->BackColor = Color::Red;
            editStudentDataButton->ForeColor = Color::White;
            editStudentDataButton->FlatStyle = FlatStyle::Flat;
            editStudentDataButton->FlatAppearance->BorderSize = 0;
            editStudentDataButton->Click += gcnew EventHandler(this, &AdminForm::OnEditStudentDataClicked);
            editStudentDataButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            editStudentDataButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            showCoursesButton = gcnew Button();
            showCoursesButton->Text = "Show Courses";
            showCoursesButton->Location = Point(20, 170);
            showCoursesButton->Size = Drawing::Size(150, 40);
            showCoursesButton->BackColor = Color::Red;
            showCoursesButton->ForeColor = Color::White;
            showCoursesButton->FlatStyle = FlatStyle::Flat;
            showCoursesButton->FlatAppearance->BorderSize = 0;
            showCoursesButton->Click += gcnew EventHandler(this, &AdminForm::OnShowCoursesClicked);
            showCoursesButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            showCoursesButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            manageGradesButton = gcnew Button();
            manageGradesButton->Text = "Manage Student Grades";
            manageGradesButton->Location = Point(20, 220);
            manageGradesButton->Size = Drawing::Size(150, 40);
            manageGradesButton->BackColor = Color::Red;
            manageGradesButton->ForeColor = Color::White;
            manageGradesButton->FlatStyle = FlatStyle::Flat;
            manageGradesButton->FlatAppearance->BorderSize = 0;
            manageGradesButton->Click += gcnew EventHandler(this, &AdminForm::OnManageGradesClicked);
            manageGradesButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            manageGradesButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            deleteUserButton = gcnew Button();
            deleteUserButton->Text = "Delete User";
            deleteUserButton->Location = Point(20, 270);
            deleteUserButton->Size = Drawing::Size(150, 40);
            deleteUserButton->BackColor = Color::Red;
            deleteUserButton->ForeColor = Color::White;
            deleteUserButton->FlatStyle = FlatStyle::Flat;
            deleteUserButton->FlatAppearance->BorderSize = 0;
            deleteUserButton->Click += gcnew EventHandler(this, &AdminForm::OnDeleteUserClicked);
            deleteUserButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            deleteUserButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            exitButton = gcnew Button();
            exitButton->Text = "Exit";
            exitButton->Location = Point(20, 320);
            exitButton->Size = Drawing::Size(150, 40);
            exitButton->BackColor = Color::Red;
            exitButton->ForeColor = Color::White;
            exitButton->FlatStyle = FlatStyle::Flat;
            exitButton->FlatAppearance->BorderSize = 0;
            exitButton->Click += gcnew EventHandler(this, &AdminForm::OnExitClicked);
            exitButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            exitButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            outputGrid = gcnew DataGridView();
            outputGrid->Location = Point(200, 180);
            outputGrid->Size = Drawing::Size(570, 350);
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
            outputGrid->Visible = false;

            defaultImage = gcnew PictureBox();
            defaultImage->Location = Point(200, 180);
            defaultImage->Size = Drawing::Size(570, 350);
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

            inputPanel = gcnew Panel();
            inputPanel->Location = Point(200, 20);
            inputPanel->Size = Drawing::Size(570, 150);
            inputPanel->BackColor = Color::White;

            this->Controls->Add(uploadCourseButton);
            this->Controls->Add(setPrerequisitesButton);
            this->Controls->Add(editStudentDataButton);
            this->Controls->Add(showCoursesButton);
            this->Controls->Add(manageGradesButton);
            this->Controls->Add(deleteUserButton);
            this->Controls->Add(exitButton);
            this->Controls->Add(outputGrid);
            this->Controls->Add(inputPanel);
            this->Controls->Add(defaultImage);
        }

    protected:
        virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override
        {
            int width = this->ClientSize.Width;
            int height = this->ClientSize.Height;
            System::Drawing::Rectangle leftRect(0, 0, 190, height);
            System::Drawing::Rectangle rightRect(190, 0, width - 190, height);
            System::Drawing::Drawing2D::LinearGradientBrush^ leftBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(leftRect, Color::White, Color::DarkGray, System::Drawing::Drawing2D::LinearGradientMode::Vertical);
            System::Drawing::Drawing2D::LinearGradientBrush^ rightBrush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(rightRect, Color::DarkGray, Color::White, System::Drawing::Drawing2D::LinearGradientMode::Vertical);
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

        void OnUploadCourseClicked(Object^ sender, EventArgs^ e)
        {
            defaultImage->Visible = false;
            isImageVisible = false;
            outputGrid->Visible = true;

            outputGrid->Columns->Clear();
            outputGrid->Rows->Clear();
            inputPanel->Controls->Clear();

            try {
                outputGrid->Columns->Add("Title", "Title");
                outputGrid->Columns->Add("Syllabus", "Syllabus");
                outputGrid->Columns->Add("CreditHours", "Credit Hours");
                outputGrid->Columns->Add("Instructor", "Instructor");
                outputGrid->Columns->Add("Prerequisites", "Prerequisites");

                for (const auto& course : dm.courses) {
                    ManagedCourse^ managedCourse = ToManagedCourse(course);
                    array<Object^>^ row = {
                        managedCourse->title,
                        managedCourse->syllabus,
                        managedCourse->creditHours.ToString(),
                        managedCourse->instructor,
                        String::IsNullOrEmpty(managedCourse->prerequisites) ? "None" : managedCourse->prerequisites
                    };
                    outputGrid->Rows->Add(row);
                }

                for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 110;
                }
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            Label^ titleLabel = gcnew Label();
            titleLabel->Text = "Course Title:";
            titleLabel->Location = Point(10, 10);
            titleLabel->Size = Drawing::Size(100, 20);
            titleBox = gcnew TextBox();
            titleBox->Location = Point(120, 10);
            titleBox->Size = Drawing::Size(150, 20);

            Label^ syllabusLabel = gcnew Label();
            syllabusLabel->Text = "Syllabus:";
            syllabusLabel->Location = Point(10, 40);
            syllabusLabel->Size = Drawing::Size(100, 20);
            syllabusBox = gcnew TextBox();
            syllabusBox->Location = Point(120, 40);
            syllabusBox->Size = Drawing::Size(150, 20);

            Label^ creditHoursLabel = gcnew Label();
            creditHoursLabel->Text = "Credit Hours:";
            creditHoursLabel->Location = Point(10, 70);
            creditHoursLabel->Size = Drawing::Size(100, 20);
            creditHoursBox = gcnew TextBox();
            creditHoursBox->Location = Point(120, 70);
            creditHoursBox->Size = Drawing::Size(150, 20);

            Label^ instructorLabel = gcnew Label();
            instructorLabel->Text = "Instructor:";
            instructorLabel->Location = Point(280, 10);
            instructorLabel->Size = Drawing::Size(100, 20);
            instructorBox = gcnew TextBox();
            instructorBox->Location = Point(390, 10);
            instructorBox->Size = Drawing::Size(150, 20);

            Button^ submitButton = gcnew Button();
            submitButton->Text = "Submit";
            submitButton->Location = Point(390, 40);
            submitButton->Size = Drawing::Size(80, 30);
            submitButton->BackColor = Color::Red;
            submitButton->ForeColor = Color::White;
            submitButton->FlatStyle = FlatStyle::Flat;
            submitButton->FlatAppearance->BorderSize = 0;
            submitButton->Click += gcnew EventHandler(this, &AdminForm::OnSubmitCourseClicked);
            submitButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            submitButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            inputPanel->Controls->Add(titleLabel);
            inputPanel->Controls->Add(titleBox);
            inputPanel->Controls->Add(syllabusLabel);
            inputPanel->Controls->Add(syllabusBox);
            inputPanel->Controls->Add(creditHoursLabel);
            inputPanel->Controls->Add(creditHoursBox);
            inputPanel->Controls->Add(instructorLabel);
            inputPanel->Controls->Add(instructorBox);
            inputPanel->Controls->Add(submitButton);
        }

        void OnSubmitCourseClicked(Object^ sender, EventArgs^ e)
        {
            String^ title = titleBox->Text;
            String^ syllabus = syllabusBox->Text;
            String^ creditHours = creditHoursBox->Text;
            String^ instructor = instructorBox->Text;

            if (String::IsNullOrEmpty(title) || String::IsNullOrEmpty(syllabus) ||
                String::IsNullOrEmpty(creditHours) || String::IsNullOrEmpty(instructor)) {
                MessageBox::Show("All fields are required!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try {
                int creditHoursInt = Int32::Parse(creditHours);
                admin->UploadCourse(
                    ToStdString(title),
                    ToStdString(syllabus),
                    creditHoursInt,
                    ToStdString(instructor)
                );
                MessageBox::Show("Course added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();
                outputGrid->Columns->Add("Title", "Title");
                outputGrid->Columns->Add("Syllabus", "Syllabus");
                outputGrid->Columns->Add("CreditHours", "Credit Hours");
                outputGrid->Columns->Add("Instructor", "Instructor");
                outputGrid->Columns->Add("Prerequisites", "Prerequisites");

                for (const auto& course : dm.courses) {
                    ManagedCourse^ managedCourse = ToManagedCourse(course);
                    array<Object^>^ row = {
                        managedCourse->title,
                        managedCourse->syllabus,
                        managedCourse->creditHours.ToString(),
                        managedCourse->instructor,
                        String::IsNullOrEmpty(managedCourse->prerequisites) ? "None" : managedCourse->prerequisites
                    };
                    outputGrid->Rows->Add(row);
                }

                for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 110;
                }
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            catch (Exception^) {
                MessageBox::Show("Invalid Credit Hours format!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnSetPrerequisitesClicked(Object^ sender, EventArgs^ e)
        {
            defaultImage->Visible = false;
            isImageVisible = false;
            outputGrid->Visible = true;

            outputGrid->Columns->Clear();
            outputGrid->Rows->Clear();
            inputPanel->Controls->Clear();

            outputGrid->Columns->Add("Title", "Title");
            outputGrid->Columns->Add("Syllabus", "Syllabus");
            outputGrid->Columns->Add("CreditHours", "Credit Hours");
            outputGrid->Columns->Add("Instructor", "Instructor");
            outputGrid->Columns->Add("Prerequisites", "Prerequisites");

            for (const auto& course : dm.courses) {
                ManagedCourse^ managedCourse = ToManagedCourse(course);
                array<Object^>^ row = {
                    managedCourse->title,
                    managedCourse->syllabus,
                    managedCourse->creditHours.ToString(),
                    managedCourse->instructor,
                    String::IsNullOrEmpty(managedCourse->prerequisites) ? "None" : managedCourse->prerequisites
                };
                outputGrid->Rows->Add(row);
            }

            for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                col->Width = 110;
            }

            Label^ titleLabel = gcnew Label();
            titleLabel->Text = "Course Title:";
            titleLabel->Location = Point(10, 10);
            titleLabel->Size = Drawing::Size(100, 20);
            titleBox = gcnew TextBox();
            titleBox->Location = Point(120, 10);
            titleBox->Size = Drawing::Size(150, 20);

            Label^ prereqLabel = gcnew Label();
            prereqLabel->Text = "Prerequisites:";
            prereqLabel->Location = Point(10, 40);
            prereqLabel->Size = Drawing::Size(100, 20);
            prereqBox = gcnew TextBox();
            prereqBox->Location = Point(120, 40);
            prereqBox->Size = Drawing::Size(150, 20);

            Button^ submitButton = gcnew Button();
            submitButton->Text = "Submit";
            submitButton->Location = Point(280, 40);
            submitButton->Size = Drawing::Size(80, 30);
            submitButton->BackColor = Color::Red;
            submitButton->ForeColor = Color::White;
            submitButton->FlatStyle = FlatStyle::Flat;
            submitButton->FlatAppearance->BorderSize = 0;
            submitButton->Click += gcnew EventHandler(this, &AdminForm::OnSubmitPrerequisitesClicked);
            submitButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            submitButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            inputPanel->Controls->Add(titleLabel);
            inputPanel->Controls->Add(titleBox);
            inputPanel->Controls->Add(prereqLabel);
            inputPanel->Controls->Add(prereqBox);
            inputPanel->Controls->Add(submitButton);
        }

        void OnSubmitPrerequisitesClicked(Object^ sender, EventArgs^ e)
        {
            String^ title = titleBox->Text;
            String^ prereqs = prereqBox->Text;

            try {
                admin->SetPrerequisites(
                    ToStdString(title),
                    ToStdString(prereqs)
                );
                MessageBox::Show("Prerequisites updated successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();
                outputGrid->Columns->Add("Title", "Title");
                outputGrid->Columns->Add("Syllabus", "Syllabus");
                outputGrid->Columns->Add("CreditHours", "Credit Hours");
                outputGrid->Columns->Add("Instructor", "Instructor");
                outputGrid->Columns->Add("Prerequisites", "Prerequisites");

                for (const auto& course : dm.courses) {
                    ManagedCourse^ managedCourse = ToManagedCourse(course);
                    array<Object^>^ row = {
                        managedCourse->title,
                        managedCourse->syllabus,
                        managedCourse->creditHours.ToString(),
                        managedCourse->instructor,
                        String::IsNullOrEmpty(managedCourse->prerequisites) ? "None" : managedCourse->prerequisites
                    };
                    outputGrid->Rows->Add(row);
                }

                for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 110;
                }
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnEditStudentDataClicked(Object^ sender, EventArgs^ e)
        {
            defaultImage->Visible = false;
            isImageVisible = false;
            outputGrid->Visible = true;

            outputGrid->Columns->Clear();
            outputGrid->Rows->Clear();
            inputPanel->Controls->Clear();

            outputGrid->Columns->Add("Username", "Username");
            outputGrid->Columns->Add("ID", "ID");
            outputGrid->Columns->Add("First Name", "First Name");
            outputGrid->Columns->Add("Last Name", "Last Name");
            outputGrid->Columns->Add("Phone", "Phone");
            outputGrid->Columns->Add("Email", "Email");
            outputGrid->Columns->Add("Password", "Password");

            for (const auto& user : dm.users) {
                ManagedUser^ managedUser = ToManagedUser(user);
                array<Object^>^ row = {
                    managedUser->username,
                    managedUser->id.ToString(),
                    managedUser->firstName,
                    managedUser->lastName,
                    managedUser->phone,
                    managedUser->email,
                    managedUser->password
                };
                outputGrid->Rows->Add(row);
            }

            for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                col->Width = 80;
            }

            Label^ usernameLabel = gcnew Label();
            usernameLabel->Text = "Username to edit:";
            usernameLabel->Location = Point(10, 10);
            usernameLabel->Size = Drawing::Size(120, 20);
            usernameBox = gcnew TextBox();
            usernameBox->Location = Point(140, 10);
            usernameBox->Size = Drawing::Size(150, 20);

            Button^ loadButton = gcnew Button();
            loadButton->Text = "Load Student";
            loadButton->Location = Point(300, 10);
            loadButton->Size = Drawing::Size(100, 30);
            loadButton->BackColor = Color::Red;
            loadButton->ForeColor = Color::White;
            loadButton->FlatStyle = FlatStyle::Flat;
            loadButton->FlatAppearance->BorderSize = 0;
            loadButton->Click += gcnew EventHandler(this, &AdminForm::OnLoadStudentClicked);
            loadButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            loadButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            inputPanel->Controls->Add(usernameLabel);
            inputPanel->Controls->Add(usernameBox);
            inputPanel->Controls->Add(loadButton);
        }

        void OnLoadStudentClicked(Object^ sender, EventArgs^ e)
        {
            System::String^ username = usernameBox->Text; // Managed string
            if (String::IsNullOrEmpty(username)) {
                MessageBox::Show("Please enter a username!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            std::string nativeUsername = msclr::interop::marshal_as<std::string>(username); // Convert to native
            UsernameFinder finder(nativeUsername);

            // Use std::find_if with the functor
            auto it = std::find_if(dm.users.begin(), dm.users.end(), finder);
            if (it != dm.users.end()) {
                inputPanel->Controls->Clear();

                Label^ idLabel = gcnew Label();
                idLabel->Text = "ID:";
                idLabel->Location = Point(10, 10);
                idLabel->Size = Drawing::Size(100, 20);
                idBox = gcnew TextBox();
                idBox->Location = Point(120, 10);
                idBox->Size = Drawing::Size(150, 20);
                idBox->Text = it->ID.ToString();

                Label^ firstNameLabel = gcnew Label();
                firstNameLabel->Text = "First Name:";
                firstNameLabel->Location = Point(10, 40);
                firstNameLabel->Size = Drawing::Size(100, 20);
                firstNameBox = gcnew TextBox();
                firstNameBox->Location = Point(120, 40);
                firstNameBox->Size = Drawing::Size(150, 20);
                firstNameBox->Text = gcnew String(it->FirstName.c_str());

                Label^ lastNameLabel = gcnew Label();
                lastNameLabel->Text = "Last Name:";
                lastNameLabel->Location = Point(10, 70);
                lastNameLabel->Size = Drawing::Size(100, 20);
                lastNameBox = gcnew TextBox();
                lastNameBox->Location = Point(120, 70);
                lastNameBox->Size = Drawing::Size(150, 20);
                lastNameBox->Text = gcnew String(it->LastName.c_str());

                Label^ phoneLabel = gcnew Label();
                phoneLabel->Text = "Phone:";
                phoneLabel->Location = Point(280, 10);
                phoneLabel->Size = Drawing::Size(100, 20);
                phoneBox = gcnew TextBox();
                phoneBox->Location = Point(390, 10);
                phoneBox->Size = Drawing::Size(150, 20);
                phoneBox->Text = gcnew String(it->PhoneNumber.c_str());

                Label^ emailLabel = gcnew Label();
                emailLabel->Text = "Email:";
                emailLabel->Location = Point(280, 40);
                emailLabel->Size = Drawing::Size(100, 20);
                emailBox = gcnew TextBox();
                emailBox->Location = Point(390, 40);
                emailBox->Size = Drawing::Size(150, 20);
                emailBox->Text = gcnew String(it->Email.c_str());

                Label^ passwordLabel = gcnew Label();
                passwordLabel->Text = "Password:";
                passwordLabel->Location = Point(280, 70);
                passwordLabel->Size = Drawing::Size(100, 20);
                passwordBox = gcnew TextBox();
                passwordBox->Location = Point(390, 70);
                passwordBox->Size = Drawing::Size(150, 20);
                passwordBox->Text = gcnew String(it->Password.c_str());

                Button^ submitButton = gcnew Button();
                submitButton->Text = "Submit";
                submitButton->Location = Point(390, 100);
                submitButton->Size = Drawing::Size(80, 30);
                submitButton->BackColor = Color::Red;
                submitButton->ForeColor = Color::White;
                submitButton->FlatStyle = FlatStyle::Flat;
                submitButton->FlatAppearance->BorderSize = 0;
                submitButton->Click += gcnew EventHandler(this, &AdminForm::OnSubmitEditStudentClicked);
                submitButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
                submitButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

                inputPanel->Controls->Add(idLabel);
                inputPanel->Controls->Add(idBox);
                inputPanel->Controls->Add(firstNameLabel);
                inputPanel->Controls->Add(firstNameBox);
                inputPanel->Controls->Add(lastNameLabel);
                inputPanel->Controls->Add(lastNameBox);
                inputPanel->Controls->Add(phoneLabel);
                inputPanel->Controls->Add(phoneBox);
                inputPanel->Controls->Add(emailLabel);
                inputPanel->Controls->Add(emailBox);
                inputPanel->Controls->Add(passwordLabel);
                inputPanel->Controls->Add(passwordBox);
                inputPanel->Controls->Add(submitButton);
            }
            else {
                MessageBox::Show("Student not found!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnSubmitEditStudentClicked(Object^ sender, EventArgs^ e)
        {
            String^ username = usernameBox->Text;
            String^ idStr = idBox->Text;
            String^ firstName = firstNameBox->Text;
            String^ lastName = lastNameBox->Text;
            String^ phone = phoneBox->Text;
            String^ email = emailBox->Text;
            String^ password = passwordBox->Text;

            if (String::IsNullOrEmpty(username)) {
                MessageBox::Show("Username is required!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try {
                int id = String::IsNullOrEmpty(idStr) ? -1 : Int32::Parse(idStr);
                admin->editStudentData(
                    ToStdString(username),
                    id,
                    ToStdString(firstName),
                    ToStdString(lastName),
                    ToStdString(phone),
                    ToStdString(email),
                    ToStdString(password)
                );
                MessageBox::Show("Student data updated successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();
                outputGrid->Columns->Add("Username", "Username");
                outputGrid->Columns->Add("ID", "ID");
                outputGrid->Columns->Add("First Name", "First Name");
                outputGrid->Columns->Add("Last Name", "Last Name");
                outputGrid->Columns->Add("Phone", "Phone");
                outputGrid->Columns->Add("Email", "Email");
                outputGrid->Columns->Add("Password", "Password");

                for (const auto& user : dm.users) {
                    ManagedUser^ managedUser = ToManagedUser(user);
                    array<Object^>^ row = {
                        managedUser->username,
                        managedUser->id.ToString(),
                        managedUser->firstName,
                        managedUser->lastName,
                        managedUser->phone,
                        managedUser->email,
                        managedUser->password
                    };
                    outputGrid->Rows->Add(row);
                }

                for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 80;
                }

                inputPanel->Controls->Clear();
                Label^ usernameLabel = gcnew Label();
                usernameLabel->Text = "Username to edit:";
                usernameLabel->Location = Point(10, 10);
                usernameLabel->Size = Drawing::Size(120, 20);
                usernameBox = gcnew TextBox();
                usernameBox->Location = Point(140, 10);
                usernameBox->Size = Drawing::Size(150, 20);

                Button^ loadButton = gcnew Button();
                loadButton->Text = "Load Student";
                loadButton->Location = Point(300, 10);
                loadButton->Size = Drawing::Size(100, 30);
                loadButton->BackColor = Color::Red;
                loadButton->ForeColor = Color::White;
                loadButton->FlatStyle = FlatStyle::Flat;
                loadButton->FlatAppearance->BorderSize = 0;
                loadButton->Click += gcnew EventHandler(this, &AdminForm::OnLoadStudentClicked);
                loadButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
                loadButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

                inputPanel->Controls->Add(usernameLabel);
                inputPanel->Controls->Add(usernameBox);
                inputPanel->Controls->Add(loadButton);
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            catch (Exception^) {
                MessageBox::Show("Invalid ID format!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnShowCoursesClicked(Object^ sender, EventArgs^ e)
        {
            defaultImage->Visible = false;
            isImageVisible = false;
            outputGrid->Visible = true;

            inputPanel->Controls->Clear();
            outputGrid->Columns->Clear();
            outputGrid->Rows->Clear();

            try {
                outputGrid->Columns->Add("Title", "Title");
                outputGrid->Columns->Add("Syllabus", "Syllabus");
                outputGrid->Columns->Add("CreditHours", "Credit Hours");
                outputGrid->Columns->Add("Instructor", "Instructor");
                outputGrid->Columns->Add("Prerequisites", "Prerequisites");

                for (const auto& course : dm.courses) {
                    ManagedCourse^ managedCourse = ToManagedCourse(course);
                    array<Object^>^ row = {
                        managedCourse->title,
                        managedCourse->syllabus,
                        managedCourse->creditHours.ToString(),
                        managedCourse->instructor,
                        String::IsNullOrEmpty(managedCourse->prerequisites) ? "None" : managedCourse->prerequisites
                    };
                    outputGrid->Rows->Add(row);
                }

                for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 110;
                }
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnManageGradesClicked(Object^ sender, EventArgs^ e)
        {
            defaultImage->Visible = false;
            isImageVisible = false;
            outputGrid->Visible = true;

            outputGrid->Columns->Clear();
            outputGrid->Rows->Clear();
            inputPanel->Controls->Clear();

            outputGrid->Columns->Add("Username", "Username");
            outputGrid->Columns->Add("ID", "ID");
            outputGrid->Columns->Add("First Name", "First Name");
            outputGrid->Columns->Add("Last Name", "Last Name");
            outputGrid->Columns->Add("Phone", "Phone");
            outputGrid->Columns->Add("Email", "Email");
            outputGrid->Columns->Add("Password", "Password");

            for (const auto& user : dm.users) {
                ManagedUser^ managedUser = ToManagedUser(user);
                array<Object^>^ row = {
                    managedUser->username,
                    managedUser->id.ToString(),
                    managedUser->firstName,
                    managedUser->lastName,
                    managedUser->phone,
                    managedUser->email,
                    managedUser->password
                };
                outputGrid->Rows->Add(row);
            }

            for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                col->Width = 80;
            }

            Label^ idLabel = gcnew Label();
            idLabel->Text = "Student ID:";
            idLabel->Location = Point(10, 10);
            idLabel->Size = Drawing::Size(100, 20);
            idBox = gcnew TextBox();
            idBox->Location = Point(120, 10);
            idBox->Size = Drawing::Size(150, 20);

            Button^ loadButton = gcnew Button();
            loadButton->Text = "Load Grades";
            loadButton->Location = Point(280, 10);
            loadButton->Size = Drawing::Size(100, 30);
            loadButton->BackColor = Color::Red;
            loadButton->ForeColor = Color::White;
            loadButton->FlatStyle = FlatStyle::Flat;
            loadButton->FlatAppearance->BorderSize = 0;
            loadButton->Click += gcnew EventHandler(this, &AdminForm::OnLoadGradesClicked);
            loadButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            loadButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            inputPanel->Controls->Add(idLabel);
            inputPanel->Controls->Add(idBox);
            inputPanel->Controls->Add(loadButton);
        }

        void OnLoadGradesClicked(Object^ sender, EventArgs^ e)
        {
            String^ idStr = idBox->Text;
            if (String::IsNullOrEmpty(idStr)) {
                MessageBox::Show("Student ID is required!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try {
                int id = Int32::Parse(idStr);
                auto regIt = dm.registrations.find(id);
                if (regIt == dm.registrations.end()) {
                    MessageBox::Show("No registrations found for this student!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return;
                }
                std::vector<std::string> registeredCourses = regIt->second;

                std::vector<std::string> coursesWithoutGrades;
                for (const auto& course : registeredCourses) {
                    bool hasGrade = false;
                    for (const auto& grade : dm.grades) {
                        if (grade.ID == id && grade.Subject == course) {
                            hasGrade = true;
                            break;
                        }
                    }
                    if (!hasGrade) {
                        coursesWithoutGrades.push_back(course);
                    }
                }

                if (coursesWithoutGrades.empty()) {
                    MessageBox::Show("All registered courses have grades!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return;
                }

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();
                outputGrid->Columns->Add("Course", "Course");

                for (const auto& course : coursesWithoutGrades) {
                    outputGrid->Rows->Add(gcnew String(course.c_str()));
                }

                for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 150;
                }

                inputPanel->Controls->Clear();
                Label^ idLabel = gcnew Label();
                idLabel->Text = "Student ID:";
                idLabel->Location = Point(10, 10);
                idLabel->Size = Drawing::Size(100, 20);
                idBox = gcnew TextBox();
                idBox->Location = Point(120, 10);
                idBox->Size = Drawing::Size(150, 20);
                idBox->Text = idStr;
                idBox->ReadOnly = true;

                Label^ subjectLabel = gcnew Label();
                subjectLabel->Text = "Subject:";
                subjectLabel->Location = Point(10, 40);
                subjectLabel->Size = Drawing::Size(100, 20);
                subjectBox = gcnew TextBox();
                subjectBox->Location = Point(120, 40);
                subjectBox->Size = Drawing::Size(150, 20);

                Label^ quizLabel = gcnew Label();
                quizLabel->Text = "Quiz (0-10):";
                quizLabel->Location = Point(10, 70);
                quizLabel->Size = Drawing::Size(100, 20);
                quizBox = gcnew TextBox();
                quizBox->Location = Point(120, 70);
                quizBox->Size = Drawing::Size(150, 20);

                Label^ assignmentLabel = gcnew Label();
                assignmentLabel->Text = "Assignment (0-10):";
                assignmentLabel->Location = Point(280, 10);
                assignmentLabel->Size = Drawing::Size(100, 20);
                assignmentBox = gcnew TextBox();
                assignmentBox->Location = Point(390, 10);
                assignmentBox->Size = Drawing::Size(150, 20);

                Label^ midtermLabel = gcnew Label();
                midtermLabel->Text = "Midterm (0-15):";
                midtermLabel->Location = Point(280, 40);
                midtermLabel->Size = Drawing::Size(100, 20);
                midtermBox = gcnew TextBox();
                midtermBox->Location = Point(390, 40);
                midtermBox->Size = Drawing::Size(150, 20);

                Label^ practicalLabel = gcnew Label();
                practicalLabel->Text = "Practical (0-20):";
                practicalLabel->Location = Point(280, 70);
                practicalLabel->Size = Drawing::Size(100, 20);
                practicalBox = gcnew TextBox();
                practicalBox->Location = Point(390, 70);
                practicalBox->Size = Drawing::Size(150, 20);

                Label^ finalLabel = gcnew Label();
                finalLabel->Text = "Final (0-60):";
                finalLabel->Location = Point(10, 100);
                finalLabel->Size = Drawing::Size(100, 20);
                finalBox = gcnew TextBox();
                finalBox->Location = Point(120, 100);
                finalBox->Size = Drawing::Size(150, 20);

                Button^ submitButton = gcnew Button();
                submitButton->Text = "Submit";
                submitButton->Location = Point(390, 100);
                submitButton->Size = Drawing::Size(80, 30);
                submitButton->BackColor = Color::Red;
                submitButton->ForeColor = Color::White;
                submitButton->FlatStyle = FlatStyle::Flat;
                submitButton->FlatAppearance->BorderSize = 0;
                submitButton->Click += gcnew EventHandler(this, &AdminForm::OnSubmitGradesClicked);
                submitButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
                submitButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

                inputPanel->Controls->Add(idLabel);
                inputPanel->Controls->Add(idBox);
                inputPanel->Controls->Add(subjectLabel);
                inputPanel->Controls->Add(subjectBox);
                inputPanel->Controls->Add(quizLabel);
                inputPanel->Controls->Add(quizBox);
                inputPanel->Controls->Add(assignmentLabel);
                inputPanel->Controls->Add(assignmentBox);
                inputPanel->Controls->Add(midtermLabel);
                inputPanel->Controls->Add(midtermBox);
                inputPanel->Controls->Add(practicalLabel);
                inputPanel->Controls->Add(practicalBox);
                inputPanel->Controls->Add(finalLabel);
                inputPanel->Controls->Add(finalBox);
                inputPanel->Controls->Add(submitButton);
            }
            catch (Exception^) {
                MessageBox::Show("Invalid Student ID format!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnSubmitGradesClicked(Object^ sender, EventArgs^ e)
        {
            String^ idStr = idBox->Text;
            String^ subject = subjectBox->Text;
            String^ quizStr = quizBox->Text;
            String^ assignmentStr = assignmentBox->Text;
            String^ midtermStr = midtermBox->Text;
            String^ practicalStr = practicalBox->Text;
            String^ finalStr = finalBox->Text;

            if (String::IsNullOrEmpty(idStr) || String::IsNullOrEmpty(subject) ||
                String::IsNullOrEmpty(quizStr) || String::IsNullOrEmpty(assignmentStr) ||
                String::IsNullOrEmpty(midtermStr) || String::IsNullOrEmpty(practicalStr) ||
                String::IsNullOrEmpty(finalStr)) {
                MessageBox::Show("All fields are required!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try {
                int id = Int32::Parse(idStr);
                int quiz = Int32::Parse(quizStr);
                int assignment = Int32::Parse(assignmentStr);
                int midterm = Int32::Parse(midtermStr);
                int practical = Int32::Parse(practicalStr);
                int finalExam = Int32::Parse(finalStr);

                if (quiz < 0 || quiz > 10 || assignment < 0 || assignment > 10 ||
                    midterm < 0 || midterm > 15 || practical < 0 || practical > 20 ||
                    finalExam < 0 || finalExam > 60) {
                    MessageBox::Show("Grades must be within the specified ranges!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                admin->manageStudentGrades(id, ToStdString(subject), quiz, assignment, midterm, practical, finalExam);
                MessageBox::Show("Grades saved successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

                OnLoadGradesClicked(sender, e);
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            catch (Exception^) {
                MessageBox::Show("Invalid number format!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnDeleteUserClicked(Object^ sender, EventArgs^ e)
        {
            defaultImage->Visible = false;
            isImageVisible = false;
            outputGrid->Visible = true;

            outputGrid->Columns->Clear();
            outputGrid->Rows->Clear();
            inputPanel->Controls->Clear();

            outputGrid->Columns->Add("Username", "Username");
            outputGrid->Columns->Add("ID", "ID");
            outputGrid->Columns->Add("First Name", "First Name");
            outputGrid->Columns->Add("Last Name", "Last Name");
            outputGrid->Columns->Add("Phone", "Phone");
            outputGrid->Columns->Add("Email", "Email");
            outputGrid->Columns->Add("Password", "Password");

            for (const auto& user : dm.users) {
                ManagedUser^ managedUser = ToManagedUser(user);
                array<Object^>^ row = {
                    managedUser->username,
                    managedUser->id.ToString(),
                    managedUser->firstName,
                    managedUser->lastName,
                    managedUser->phone,
                    managedUser->email,
                    managedUser->password
                };
                outputGrid->Rows->Add(row);
            }

            for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                col->Width = 80;
            }

            Label^ idLabel = gcnew Label();
            idLabel->Text = "User ID:";
            idLabel->Location = Point(10, 10);
            idLabel->Size = Drawing::Size(100, 20);
            idBox = gcnew TextBox();
            idBox->Location = Point(120, 10);
            idBox->Size = Drawing::Size(150, 20);

            Button^ submitButton = gcnew Button();
            submitButton->Text = "Delete";
            submitButton->Location = Point(280, 10);
            submitButton->Size = Drawing::Size(80, 30);
            submitButton->BackColor = Color::Red;
            submitButton->ForeColor = Color::White;
            submitButton->FlatStyle = FlatStyle::Flat;
            submitButton->FlatAppearance->BorderSize = 0;
            submitButton->Click += gcnew EventHandler(this, &AdminForm::OnSubmitDeleteUserClicked);
            submitButton->MouseEnter += gcnew EventHandler(this, &AdminForm::OnButtonHover);
            submitButton->MouseLeave += gcnew EventHandler(this, &AdminForm::OnButtonLeave);

            inputPanel->Controls->Add(idLabel);
            inputPanel->Controls->Add(idBox);
            inputPanel->Controls->Add(submitButton);
        }

        void OnSubmitDeleteUserClicked(Object^ sender, EventArgs^ e)
        {
            String^ idStr = idBox->Text;
            if (String::IsNullOrEmpty(idStr)) {
                MessageBox::Show("User ID is required!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try {
                int id = Int32::Parse(idStr);
                bool undo = false;
                User deletedUser;
                admin->deleteUser(id, undo, deletedUser);
                MessageBox::Show("User deleted successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

                if (MessageBox::Show("Do you want to undo the deletion?", "Undo",
                    MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
                    undo = true;
                    dm.users.push_back(deletedUser);
                    dm.writeUsers("database.csv");
                    MessageBox::Show("Deletion undone. User restored.", "Success",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                }

                outputGrid->Columns->Clear();
                outputGrid->Rows->Clear();
                outputGrid->Columns->Add("Username", "Username");
                outputGrid->Columns->Add("ID", "ID");
                outputGrid->Columns->Add("First Name", "First Name");
                outputGrid->Columns->Add("Last Name", "Last Name");
                outputGrid->Columns->Add("Phone", "Phone");
                outputGrid->Columns->Add("Email", "Email");
                outputGrid->Columns->Add("Password", "Password");

                for (const auto& user : dm.users) {
                    ManagedUser^ managedUser = ToManagedUser(user);
                    array<Object^>^ row = {
                        managedUser->username,
                        managedUser->id.ToString(),
                        managedUser->firstName,
                        managedUser->lastName,
                        managedUser->phone,
                        managedUser->email,
                        managedUser->password
                    };
                    outputGrid->Rows->Add(row);
                }

                for each (DataGridViewColumn ^ col in outputGrid->Columns) {
                    col->Width = 80;
                }
            }
            catch (const std::exception& ex) {
                MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            catch (Exception^) {
                MessageBox::Show("Invalid ID format!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
                inputPanel->Controls->Clear();
            }
        }
    };
}