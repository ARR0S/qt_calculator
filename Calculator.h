#pragma once

#include <numbers>
#include <QWidget>
#include <QLineEdit>
#include <QMenu>
#include <QEvent>
#include <QGridLayout>
#include <QRegularExpression>
#include "MyButton.h"

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    QString style;
private slots:
    void digitClicked();
    void binaryOperatorClicked();
    void unaryOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void tenxClicked();
    void twoxClicked();
    void exClicked();
    void powClicked();
    void logClicked();
    void rootClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void addToMemory();
    void minToMemory();
    void selectorClicked();
    void trigClicked();
    void trigOperatorClicked();
    void expClicked();
    void sec1Clicked();
    void hipClicked();
    void constClicked();
    void degRadClicked();
private:
    MyButton* createButton(const QString& text, const char* member);
    double m_sum_in_mem;
    QLineEdit* m_display_up;
    QLineEdit* m_display_down;
    MyButton* m_digitButtons[10];
    MyButton* pointButton;
    MyButton* changeSignButton;
    MyButton* backspaceButton;
    MyButton* clearButton;
    MyButton* clearAllSignButton;
    MyButton* clearMemoryButton;
    MyButton* readMemoryButton;
    MyButton* addMemoryButton;
    MyButton* minToMemoryButton;
    MyButton* divisionButton;
    MyButton* timesButton;
    MyButton* minusButton;
    MyButton* plusButton;
    MyButton* squareRootButton;
    MyButton* squaredButton;
    MyButton* reciprocalButton;
    MyButton* equalButton;
    MyButton* selectorButton;
    MyButton* trigonometryButton;
    MyButton* modButton;
    MyButton* expButton;
    MyButton* absButton;
    MyButton* factButton;
    MyButton* piButton;
    MyButton* eButton;
    MyButton* sec1Button;
    MyButton* hipButton;
    MyButton* cubeButton;
    MyButton* cubeRootButton;
    MyButton* powButton;
    MyButton* rootButton;
    MyButton* tenxButton;
    MyButton* twoxButton;
    MyButton* lgButton;
    MyButton* logButton;
    MyButton* lnButton;
    MyButton* exButton;
    MyButton* degRadButton;
    MyButton* sinButton;
    MyButton* asinButton;
    MyButton* cosButton;
    MyButton* acosButton;
    MyButton* tanButton;
    MyButton* atanButton;
    MyButton* sinhButton;
    MyButton* asinhButton;
    MyButton* coshButton;
    MyButton* acoshButton;
    MyButton* tanhButton;
    MyButton* atanhButton;
    QGridLayout* mainLayout;
    QString m_square_root = QChar(0x0000221A);
    QString m_squared = 'x' + QChar(0x000000b2);
    QString m_reciprocal = "1/x";
    QString m_division = QChar(0x000000F7);
    QString m_times = QChar(0x000000D7);
    QString m_plus = "+";
    QString m_minus = "-";
    QString m_change = QChar(0x000000b1);
    QString m_backspace = QChar(0x000021D0);
    QString m_selector = QChar(0x00002261);
    QString m_pi = QChar(0x000003C0);
    QString m_e = QChar(0x00000065);
    QString m_fact = "n!";
    QString m_cubed = 'x' + QChar(0x000000B3);
    QString m_cube_root = QChar(0x0000221B);
    QString m_lg = "log(x)";
    QString m_ln = "ln(x)";
    bool m_after_binary_op = false;
    bool m_binary_op_before_equal = false;
    bool m_after_unary_op = false;
    bool after_abortion = false;
    bool digit_clicked = false;
    bool equal_clicked = false;
    bool exp_clicked = false;
    bool overflow = false;
    bool sec1_clicked = false;
    bool trig_clicked = false;
    bool hip_clicked = false;
    QString m_double_op;
    QString m_unary_op;
    void abortOperation();
    void setStandart();
    void setAdvanced();
    void clearLayout(QLayout* layout);
};
