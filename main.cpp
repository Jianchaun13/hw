#include <QApplication>
#include <QWidget>
#include <QTabWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QFontDialog>

void setupUi(QWidget*);
void leader(QTabWidget*, QTextBrowser*&);
void change_color(QTabWidget*, QTextBrowser*);
void changeFont(QTabWidget* tabWidget, const QFont& font);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget* windows = new QWidget;
    setupUi(windows);
    windows->show();
    return a.exec();
}

void setupUi(QWidget *windows)
{
    QTabWidget *tabWidget;
    QTextBrowser *leaderTextBrowser;  // 儲存隊長的文字框框

    QVBoxLayout *mainLayout = new QVBoxLayout(windows);

    // windows setting
    if (windows->objectName().isEmpty())
    {
        windows->setObjectName("Form");
    }
    windows->resize(300, 300);
    windows->setWindowTitle("第4組");

    tabWidget = new QTabWidget(windows);
    tabWidget->setObjectName("tabWidget");

    // Tab 1 - 隊長
    leader(tabWidget, leaderTextBrowser);

    // Tab 2 - 組員1
    QWidget* tab_1 = new QWidget;
    tab_1->setObjectName("tab1");
    tabWidget->addTab(tab_1, "組員1");

    // Tab 3 - 組員2
    QWidget* tab_2 = new QWidget;
    tab_2->setObjectName("tab2");
    QVBoxLayout* layout_2 = new QVBoxLayout(tab_2);
    QPushButton* button = new QPushButton("Font select", tab_2);
    //加入點按鈕的事件
    QObject::connect(button, &QPushButton::clicked, [=]() {
        bool ok;
        QFont font = QFontDialog::getFont(&ok, QFont(), windows);
        if (ok) {
            //會改變字體 NICE
            changeFont(tabWidget, font);
        }
    });
    layout_2->addWidget(button);
    tab_2->setLayout(layout_2);
    tabWidget->addTab(tab_2, "組員2");

    // Tab 3 - 組員3
    QWidget* tab_3 = new QWidget;
    tab_3->setObjectName("tab3");
    tabWidget->addTab(tab_3, "組員3");

    // 一開始顯示隊長頁面
    tabWidget->setCurrentIndex(0);

    mainLayout->addWidget(tabWidget);

    windows->setLayout(mainLayout);

    QMetaObject::connectSlotsByName(windows);
}

void leader(QTabWidget* tabWidget, QTextBrowser*& leaderTextBrowser) {
    QWidget *tab;
    tab = new QWidget();
    tab->setObjectName("tab");

    // 新增佈局自動調整大小
    QVBoxLayout* tabLayout = new QVBoxLayout(tab);

    // 新增文字框
    leaderTextBrowser = new QTextBrowser(tab);
    leaderTextBrowser->setObjectName("textBrowser");
    leaderTextBrowser->setText("\n\n"
                               "隊長:   41243122 林建全\n"
                               "組員1: 41243101 伍翊瑄\n"
                               "組員2: 41243129 張帟淇\n"
                               "組員3: 41243249 劉仲恩" "");

    tabLayout->addWidget(leaderTextBrowser);

    tab->setLayout(tabLayout);
    tabWidget->addTab(tab, "隊長");
}
void changeFont(QTabWidget* tabWidget, const QFont& font) {     //這是改變字體的函式  GOOD
    for (int i = 0; i < tabWidget->count(); ++i) {
        QWidget* tab = tabWidget->widget(i);
        QTextBrowser* textBrowser = tab->findChild<QTextBrowser*>();
        if (textBrowser) {
            textBrowser->setFont(font);
        }
    }
}
