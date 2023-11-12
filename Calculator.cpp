#include "Calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), m_sum_in_mem(0.0)
{
    m_display_down = new QLineEdit();
    m_display_down->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_display_down->setObjectName("m_display_down");
    m_display_up = new QLineEdit();
    m_display_up->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_display_down->setReadOnly(1);
    m_display_down->setText("0");
    m_display_down->setAlignment(Qt::AlignRight);
    m_display_down->setMaxLength(30);
    m_display_up->setReadOnly(1);
    m_display_up->setAlignment(Qt::AlignRight);
    m_display_up->setMaxLength(100);
    for (int i = 0; i < 10; ++i)
    {
        m_digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
        m_digitButtons[i]->setObjectName("mainButton");
    }
    selectorButton = createButton(m_selector, SLOT(selectorClicked()));
    pointButton = createButton(",", SLOT(pointClicked()));
    changeSignButton = createButton(m_change, SLOT(changeSignClicked()));
    backspaceButton = createButton(m_backspace, SLOT(backspaceClicked()));
    clearButton = createButton("CE", SLOT(clear()));
    clearAllSignButton = createButton("C", SLOT(clearAll()));
    clearMemoryButton = createButton("MC", SLOT(clearMemory()));
    readMemoryButton = createButton("MR", SLOT(readMemory()));
    addMemoryButton = createButton("M+", SLOT(addToMemory()));
    minToMemoryButton = createButton("M-", SLOT(minToMemory()));
    divisionButton = createButton(m_division, SLOT(binaryOperatorClicked()));
    timesButton = createButton(m_times, SLOT(binaryOperatorClicked()));
    minusButton = createButton(m_minus, SLOT(binaryOperatorClicked()));
    plusButton = createButton(m_plus, SLOT(binaryOperatorClicked()));
    squareRootButton = createButton(m_square_root, SLOT(unaryOperatorClicked()));
    squaredButton = createButton(m_squared, SLOT(unaryOperatorClicked()));
    reciprocalButton = createButton(m_reciprocal, SLOT(unaryOperatorClicked()));
    equalButton = createButton("=", SLOT(equalClicked()));
    changeSignButton = createButton(m_change, SLOT(changeSignClicked()));
    trigonometryButton = createButton("TRIG", SLOT(trigClicked()));
    modButton = createButton("mod", SLOT(binaryOperatorClicked()));
    expButton = createButton("exp", SLOT(expClicked()));
    absButton = createButton("|x|", SLOT(unaryOperatorClicked()));
    factButton = createButton(m_fact, SLOT(unaryOperatorClicked()));
    piButton = createButton(m_pi, SLOT(constClicked()));
    eButton = createButton(m_e, SLOT(constClicked()));
    sec1Button = createButton("2nd", SLOT(sec1Clicked()));
    hipButton = createButton("HIP", SLOT(hipClicked()));
    cubeButton = createButton(m_cubed, SLOT(unaryOperatorClicked()));
    cubeRootButton = createButton(m_cube_root, SLOT(unaryOperatorClicked()));
    powButton = createButton("", SLOT(powClicked()));
    rootButton = createButton("", SLOT(rootClicked()));
    tenxButton = createButton("", SLOT(tenxClicked()));
    twoxButton = createButton("", SLOT(twoxClicked()));
    lgButton = createButton(m_lg, SLOT(unaryOperatorClicked()));
    logButton = createButton("", SLOT(logClicked()));
    lnButton = createButton(m_ln, SLOT(unaryOperatorClicked()));
    exButton = createButton("", SLOT(exClicked()));
    degRadButton = createButton("DEG", SLOT(degRadClicked()));
    sinButton = createButton("sin", SLOT(trigOperatorClicked()));
    asinButton = createButton("asin", SLOT(trigOperatorClicked()));
    cosButton = createButton("cos", SLOT(trigOperatorClicked()));
    acosButton = createButton("acos", SLOT(trigOperatorClicked()));
    tanButton = createButton("tan", SLOT(trigOperatorClicked()));
    atanButton = createButton("atan", SLOT(trigOperatorClicked()));
    sinhButton = createButton("sinh", SLOT(trigOperatorClicked()));
    asinhButton = createButton("asinh", SLOT(trigOperatorClicked()));
    coshButton = createButton("cosh", SLOT(trigOperatorClicked()));
    acoshButton = createButton("acosh", SLOT(trigOperatorClicked()));
    tanhButton = createButton("tanh", SLOT(trigOperatorClicked()));
    atanhButton = createButton("atanh", SLOT(trigOperatorClicked()));
    pointButton->setObjectName("mainButton");
    changeSignButton->setObjectName("mainButton");
    clearMemoryButton->setObjectName("MemoryButton");
    readMemoryButton->setObjectName("MemoryButton");
    addMemoryButton->setObjectName("MemoryButton");
    minToMemoryButton->setObjectName("MemoryButton");
    selectorButton->setObjectName("selector");
    degRadButton->setObjectName("MemoryButton");
    equalButton->setObjectName("equalButton");
    powButton->setLayout(new QVBoxLayout);
    tenxButton->setLayout(new QVBoxLayout);
    exButton->setLayout(new QVBoxLayout);
    twoxButton->setLayout(new QVBoxLayout);
    rootButton->setLayout(new QVBoxLayout);
    logButton->setLayout(new QVBoxLayout);
    pow = new QLabel("x<sup>y</sup>");
    pow->setAlignment(Qt::AlignCenter);
    powButton->layout()->addWidget(pow);
    root = new QLabel("<p><sup>y</sup>&radic;x</p>");
    root->setAlignment(Qt::AlignCenter);
    rootButton->layout()->addWidget(root);
    log = new QLabel("<p>log<sub>y</sub><span>x</span></p>");
    log->setAlignment(Qt::AlignCenter);
    logButton->layout()->addWidget(log);
    tenx = new QLabel("10<sup>x</sup>");
    tenx->setAlignment(Qt::AlignCenter);
    tenxButton->layout()->addWidget(tenx);
    twox = new QLabel("2<sup>x</sup>");
    twox->setAlignment(Qt::AlignCenter);
    twoxButton->layout()->addWidget(twox);
    ex = new QLabel("e<sup>x</sup>");
    ex->setAlignment(Qt::AlignCenter);
    exButton->layout()->addWidget(ex);
    mainLayout = new QGridLayout;
    mainLayout->setSpacing(2);
    setStandart();
}

void Calculator::digitClicked()
{
    if (equal_clicked)
    {
        m_binary_op_before_equal = false;
    }
    digit_clicked = true;
    MyButton* btn = qobject_cast<MyButton*>(sender());
    if (btn==nullptr)
    {
        return;
    }
    int digit = btn->text().toUInt();
    if (exp_clicked and digit == 0)
    {
        return;
    }
    if (m_display_down->text() == "0"
        or
        m_after_binary_op 
        or
        m_after_unary_op
        or
        after_abortion
        or
        equal_clicked
        or
        overflow)
    {
        if (equal_clicked)
            m_display_up->clear();
        m_after_binary_op = false;
        m_after_unary_op = false;
        after_abortion = false;
        equal_clicked = false;
        overflow = false;
        m_display_down->clear();
    }
    QString text = m_display_down->text();
    if (exp_clicked)
    {
        text.chop(1);
    }
    exp_clicked=false;
    m_display_down->setText(text + QString::number(digit));
}

void Calculator::binaryOperatorClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    exp_clicked = false;
    m_after_unary_op = false;
    m_after_binary_op = true;
    m_binary_op_before_equal = true;
    equal_clicked = false;
    MyButton* btn = qobject_cast<MyButton*>(sender());
    if (btn == nullptr)
    {
        return;
    }
    m_double_op = btn->text();
    if (!digit_clicked)
    {
        m_display_up->setText(QString::number(m_display_down->text().toDouble()) + m_double_op);
    }
    else
    {
        QString upper = m_display_up->text();
        QString prev_op;
        if (!upper.isEmpty())
        {
            prev_op = upper.last(1);
            upper.chop(1);
        }
        else
        {
            m_display_up->setText(QString::number(m_display_down->text().toDouble()) + m_double_op);
            digit_clicked = false;
            return;
        }
        if (prev_op == m_plus)
        {
            m_display_down->setText(QString::number(upper.toDouble() + m_display_down->text().toDouble()));
        }
        else if (prev_op == m_minus)
        {
            m_display_down->setText(QString::number(upper.toDouble() - m_display_down->text().toDouble()));
        }
        else if (prev_op == m_times)
        {
            m_display_down->setText(QString::number(upper.toDouble() * m_display_down->text().toDouble()));
        }
        else if (prev_op == "mod")
        {
            m_display_down->setText(QString::number(std::fmod(upper.toDouble(), m_display_down->text().toDouble())));
        }
        else if (prev_op == m_division)
        {
            if (m_display_down->text() == "0")
            {
                abortOperation();
            }
            else
            {
                m_display_down->setText(QString::number(upper.toDouble() / m_display_down->text().toDouble()));
            }
        }
        prev_op = m_double_op;
        if (!after_abortion)
        {
            m_display_up->setText(m_display_down->text() + m_double_op);
        }
        digit_clicked = false;
    }
}

void Calculator::unaryOperatorClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (equal_clicked)
    {
        m_binary_op_before_equal = false;
        m_display_up->clear();
    }
    equal_clicked = false;
    exp_clicked = false;
    MyButton* btn = qobject_cast<MyButton*>(sender());
    if (btn == nullptr)
    {
        return;
    }
    m_unary_op = btn->text();
    QString upper = m_display_up->text();
    if (m_unary_op == m_square_root)
    {
        if (m_display_down->text().toDouble() < 0)
        {
            abortOperation();
        }
        else
        {
            if (!m_binary_op_before_equal)
            {
                m_display_up->setText(m_square_root + m_display_down->text());
            }
            else if (!digit_clicked)
            {
                bool flag = false;
                QString minus = "-";
                if (upper[0] == '-')
                {
                    upper.remove(0, 1);
                    flag = true;
                }
                upper = upper.split(m_double_op)[0];
                if (flag)
                {
                    upper = minus + upper;
                }
                m_display_up->setText(upper+m_double_op + m_square_root + m_display_down->text());
            }
            else
            {
                m_display_up->setText(upper + m_square_root + m_display_down->text());
            }
            m_display_down->setText(QString::number(std::sqrt(m_display_down->text().toDouble())));
        }
    }
    else if (m_unary_op == m_cube_root)
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText(m_cube_root + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + m_cube_root + m_display_down->text());

        }
        else
        {
            m_display_up->setText(upper + m_cube_root + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::pow(m_display_down->text().toDouble(),1./3)));
    }
    else if (m_unary_op == m_squared)
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("(" + m_display_down->text() + ")^2");
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper+m_double_op + "(" + m_display_down->text() + ")^2");
        }
        else
        {
            m_display_up->setText(upper + "(" + m_display_down->text() + ")^2");                
        }
        m_display_down->setText(QString::number(m_display_down->text().toDouble() * m_display_down->text().toDouble()));
    }
    else if (m_unary_op == m_cubed)
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("(" + m_display_down->text() + ")^3");
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "(" + m_display_down->text() + ")^3");
        }
        else
        {
            m_display_up->setText(upper + "(" + m_display_down->text() + ")^3");
        }
        m_display_down->setText(QString::number(m_display_down->text().toDouble() * m_display_down->text().toDouble() * m_display_down->text().toDouble()));
    }
    else if (m_unary_op == m_fact)
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("(" + m_display_down->text() + ")!");
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "(" + m_display_down->text() + ")!");
        }
        else
        {
            m_display_up->setText(upper + "(" + m_display_down->text() + ")!");
        }
        auto res = m_display_down->text().toDouble();
        if (std::fmod(res,1.)!=0)
        {
            abortOperation();
        }
        else
        {
            for (int i = res - 1; i > 1; --i)
            {
                res *= i;
                if (res == INFINITY)
                {
                    m_display_up->clear();
                    m_display_down->setText("OVERFLOW");
                    overflow = true;
                    return;
                }
            }
            m_display_down->setText(QString::number(res));
        }
    }
    else if (m_unary_op == "|x|")
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("|" + m_display_down->text() + "|");
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "|" + m_display_down->text() + "|");
        }
        else
        {
            m_display_up->setText(upper + "|" + m_display_down->text() + "|");
        }
        if (m_display_down->text()[0] == '-')
            m_display_down->setText(m_display_down->text().remove(0, 1));
    }
    else if (m_unary_op == m_reciprocal)
    {
        if (m_display_down->text() == "0")
        {
            abortOperation();
        }
        else
        {
            if (!m_binary_op_before_equal)
            {
                m_display_up->setText("1/(" + m_display_down->text() + ")");
            }
            else if (!digit_clicked)
            {
                bool flag = false;
                QString minus = "-";
                if (upper[0] == '-')
                {
                    upper.remove(0, 1);
                    flag = true;
                }
                upper = upper.split(m_double_op)[0];
                if (flag)
                {
                    upper = minus + upper;
                }
                m_display_up->setText(upper+m_double_op + "1/(" + m_display_down->text() + ")");
            }
            else
            {
                m_display_up->setText(upper + "1/(" + m_display_down->text() + ")");
            }
            m_display_down->setText(QString::number(1. / m_display_down->text().toDouble()));
        }
    }
    else if (m_unary_op == m_ln)
    {
        if (m_display_down->text().toDouble() <= 0)
        {
            abortOperation();
        }
        else
        {
            if (!m_binary_op_before_equal)
            {
                m_display_up->setText("ln(" + m_display_down->text() + ")");
            }
            else if (!digit_clicked)
            {
                bool flag = false;
                QString minus = "-";
                if (upper[0] == '-')
                {
                    upper.remove(0, 1);
                    flag = true;
                }
                upper = upper.split(m_double_op)[0];
                if (flag)
                {
                    upper = minus + upper;
                }
                m_display_up->setText(upper + m_double_op + "ln(" + m_display_down->text() + ")");
            }
            else
            {
                m_display_up->setText(upper + "ln(" + m_display_down->text() + ")");
            }
            m_display_down->setText(QString::number(std::log(m_display_down->text().toDouble())));
        }
    }
    else if (m_unary_op == m_lg)
    {
        if (m_display_down->text().toDouble() <= 0)
        {
            abortOperation();
        }
        else
        {
            if (!m_binary_op_before_equal)
            {
                m_display_up->setText("log(" + m_display_down->text() + ")");
            }
            else if (!digit_clicked)
            {
                bool flag = false;
                QString minus = "-";
                if (upper[0] == '-')
                {
                    upper.remove(0, 1);
                    flag = true;
                }
                upper = upper.split(m_double_op)[0];
                if (flag)
                {
                    upper = minus + upper;
                }
                m_display_up->setText(upper + m_double_op + "log(" + m_display_down->text() + ")");
            }
            else
            {
                m_display_up->setText(upper + "log(" + m_display_down->text() + ")");
            }
            m_display_down->setText(QString::number(std::log10(m_display_down->text().toDouble())));
        }
    }
    if (m_display_down->text() == "inf")
    {
        m_display_up->clear();
        m_display_down->setText("OVERFLOW");
        overflow = true;
    }
    m_after_unary_op = true;
    digit_clicked = false;
}

void Calculator::equalClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (m_display_up->text() == "")
    {
        m_display_up->setText(m_display_down->text() + "=");
        equal_clicked = true;
        return;
    }
    QString upper;
    QString down;
    if (equal_clicked)
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText(m_display_down->text()+"=");
            return;
        }
        QString text = m_display_up->text();
        bool eflag = false;
        bool flag = false;
        if (text.contains("e"))
        {
            if (m_double_op == "+")
            {
                auto eind1 = text.lastIndexOf("e+");
                auto eind2 = text.indexOf("e+");
                auto plusind1 = text.lastIndexOf("+");
                auto plusind2 = text.indexOf("+");
                if (eind1 < plusind1 - 1 and eind2==plusind2-1)
                {
                    down = text.mid(plusind1 + 1);
                    down.chop(1);
                }
                else if (eind2 > plusind2 - 1 and eind1 == plusind1 - 1)
                {
                    down = text.mid(plusind2 + 1);
                    down.chop(1);
                }
                else
                {
                    auto middlePlusIndex = text.indexOf("+", plusind2 + 1);
                    down = text.mid(middlePlusIndex + 1);
                    down.chop(1);
                }
                eflag = true;
            }
            else if (m_double_op == "-")
            {
                if (text[0] == '-');
                {
                    text.remove(0, 1);
                    flag = true;
                }
                auto eind1 = text.lastIndexOf("e-");
                auto eind2 = text.indexOf("e-");
                auto minind1 = text.lastIndexOf("-");
                auto minind2 = text.indexOf("-");
                if (eind1 < minind1 - 1 and eind2 == minind2 - 1)
                {
                    down = text.mid(minind1 + 1);
                    down.chop(1);
                }
                else if (eind2 > minind2 - 1 and eind1 == minind1 - 1)
                {
                    down = text.mid(minind2 + 1);
                    down.chop(1);
                }
                else
                {
                    auto middlePlusIndex = text.indexOf("-", minind2 + 1);
                    down = text.mid(middlePlusIndex + 1);
                    down.chop(1);
                }
                eflag = true;
            }
        }
        if (!eflag)
        {
            if (text[0] == '-')
            {
                text.remove(0, 1);
                flag = true;
            }
            auto list = text.split(m_double_op);
            down = list[1];
            down.chop(1);
            upper = m_display_down->text();
            if (flag)
            {
                upper = '-' + upper;
            }
        }
        upper = m_display_down->text();
    }
    else
    {
        if (m_after_unary_op)
        {
            bool flag = false;
            QString minus = "-";
            upper = m_display_up->text();
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            if (upper.contains("e"))
            {
                if (m_double_op == "+")
                {
                    auto eind1 = upper.lastIndexOf("e+");
                    auto eind2 = upper.indexOf("e+");
                    auto plusind1 = upper.lastIndexOf("+");
                    auto plusind2 = upper.indexOf("+");
                    if (eind1 < plusind1 - 1 and eind2 == plusind2 - 1)
                    {
                        upper = upper.mid(0,plusind1);
                    }
                    else if (eind2 > plusind2 - 1 and eind1 == plusind1 - 1)
                    {
                        upper = upper.mid(0,plusind2);
                    }
                    else
                    {
                        auto middlePlusIndex = upper.indexOf("+", plusind2 + 1);
                        upper = upper.mid(0, middlePlusIndex);
                    }
                }
                else if (m_double_op == "-")
                {
                    auto eind1 = upper.lastIndexOf("e-");
                    auto eind2 = upper.indexOf("e-");
                    auto minind1 = upper.lastIndexOf("-");
                    auto minind2 = upper.indexOf("-");
                    if (eind1 < minind1 - 1 and eind2 == minind2 - 1)
                    {
                        upper = upper.mid(0, minind1);
                    }
                    else if (eind2 > minind2 - 1 and eind1 == minind1 - 1)
                    {
                        upper = upper.mid(0, minind2);
                    }
                    else
                    {
                        auto middlePlusIndex = upper.indexOf("-", minind2 + 1);
                        upper = upper.mid(0, middlePlusIndex);
                    }
                }
            }
            else
            {
                upper = upper.split(m_double_op)[0];
            }
            if (flag)
            {
                upper = minus + upper;
            }
            down = m_display_down->text();
        }
        else
        {
            upper = m_display_up->text();
            upper.chop(m_double_op.size());
            down = m_display_down->text();
        }
    }
    if (m_binary_op_before_equal)
    {
        if (m_double_op == m_plus)
        {
            m_display_down->setText(QString::number(upper.toDouble() + down.toDouble()));
        }
        else if (m_double_op == m_minus)
        {
            m_display_down->setText(QString::number(upper.toDouble() - down.toDouble()));
        }
        else if (m_double_op == m_times)
        {
            m_display_down->setText(QString::number(upper.toDouble() * down.toDouble()));
        }
        else if (m_double_op == "mod")
        {
            m_display_down->setText(QString::number(std::fmod(upper.toDouble() , down.toDouble())));
        }
        else if (m_double_op == m_division)
        {
            if (m_display_down->text() == "0")
            {
                abortOperation();
            }
            else
            {
                m_display_down->setText(QString::number(upper.toDouble() / down.toDouble()));
            }
        }
        else if (m_double_op == "^")
        {
            m_display_down->setText(QString::number(std::pow(upper.toDouble(),down.toDouble())));
        }
        else if (m_double_op == " log base ")
        {
            m_display_down->setText(QString::number(std::log(upper.toDouble())/std::log(down.toDouble())));
        }
        else if (m_double_op == " root ")
        {
            m_display_down->setText(QString::number(std::pow(upper.toDouble(), 1/down.toDouble())));
        }
        m_display_up->setText(upper + m_double_op + down + "=");
        if (m_display_down->text() == "inf")
        {
            m_display_up->clear();
            m_display_down->setText("OVERFLOW");
            overflow = true;
        }
    }
    else
    {
        m_display_up->setText(m_display_up->text() + "=");
    }
    if (m_display_up->text().contains("--"))
    {
        m_display_up->setText(m_display_up->text().replace("--", "+"));
    }
    else if (m_display_up->text().contains("+-"))
    {
        m_display_up->setText(m_display_up->text().replace("+-", "-"));
    }
    m_after_unary_op = false;
    m_after_binary_op = false;
    equal_clicked = true;
    digit_clicked = false;
}

void Calculator::pointClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (!m_display_down->text().contains("."))
        m_display_down->setText(m_display_down->text() + ".");
}

void Calculator::changeSignClicked()
{
    if (m_display_down->text() == "0")
    {
        return;
    }
    digit_clicked = true;
    if (m_display_down->text()[0] == '-')
    {
        m_display_down->setText(m_display_down->text().remove(0,1));
    }
    else m_display_down->setText("-"+m_display_down->text());
}

void Calculator::backspaceClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (m_binary_op_before_equal and m_after_unary_op) return;
    if (equal_clicked or m_display_down->text().contains("e"))
    {
        m_display_up->setText("");
        equal_clicked = false;
        return;
    }
    QString text = m_display_down->text();
    text.chop(1);
    if (text.isEmpty())
    {
        text = "0";
    }
    m_display_down->setText(text);
}

void Calculator::tenxClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (equal_clicked)
    {
        m_binary_op_before_equal = false;
        m_display_up->clear();
    }
    equal_clicked = false;
    exp_clicked = false;
    QString upper = m_display_up->text();
    if (!m_binary_op_before_equal)
    {
        m_display_up->setText("10^" + m_display_down->text());
    }
    else if (!digit_clicked)
    {
        bool flag = false;
        QString minus = "-";
        if (upper[0] == '-')
        {
            upper.remove(0, 1);
            flag = true;
        }
        upper = upper.split(m_double_op)[0];
        if (flag)
        {
            upper = minus + upper;
        }
        m_display_up->setText(upper + m_double_op + "10^" + m_display_down->text());
    }
    else
    {
        m_display_up->setText(upper + "10^" + m_display_down->text());
    }
    m_display_down->setText(QString::number(std::pow(10,m_display_down->text().toDouble())));
    if (m_display_down->text() == "inf")
    {
        m_display_up->clear();
        m_display_down->setText("OVERFLOW");
        overflow = true;
    }
    m_after_unary_op = true;
    digit_clicked = false;
}

void Calculator::twoxClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (equal_clicked)
    {
        m_binary_op_before_equal = false;
        m_display_up->clear();
    }
    equal_clicked = false;
    exp_clicked = false;
    QString upper = m_display_up->text();
    if (!m_binary_op_before_equal)
    {
        m_display_up->setText("2^" + m_display_down->text());
    }
    else if (!digit_clicked)
    {
        bool flag = false;
        QString minus = "-";
        if (upper[0] == '-')
        {
            upper.remove(0, 1);
            flag = true;
        }
        upper = upper.split(m_double_op)[0];
        if (flag)
        {
            upper = minus + upper;
        }
        m_display_up->setText(upper + m_double_op + "2^" + m_display_down->text());
    }
    else
    {
        m_display_up->setText(upper + "2^" + m_display_down->text());
    }
    m_display_down->setText(QString::number(std::pow(2, m_display_down->text().toDouble())));
    if (m_display_down->text() == "inf")
    {
        m_display_up->clear();
        m_display_down->setText("OVERFLOW");
        overflow = true;
    }
    m_after_unary_op = true;
    digit_clicked = false;
}

void Calculator::exClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (equal_clicked)
    {
        m_binary_op_before_equal = false;
        m_display_up->clear();
    }
    equal_clicked = false;
    exp_clicked = false;
    QString upper = m_display_up->text();
    if (!m_binary_op_before_equal)
    {
        m_display_up->setText("e^" + m_display_down->text());
    }
    else if (!digit_clicked)
    {
        bool flag = false;
        QString minus = "-";
        if (upper[0] == '-')
        {
            upper.remove(0, 1);
            flag = true;
        }
        upper = upper.split(m_double_op)[0];
        if (flag)
        {
            upper = minus + upper;
        }
        m_display_up->setText(upper + m_double_op + "e^" + m_display_down->text());
    }
    else
    {
        m_display_up->setText(upper + "e^" + m_display_down->text());
    }
    m_display_down->setText(QString::number(std::pow(std::numbers::e, m_display_down->text().toDouble())));
    if (m_display_down->text() == "inf")
    {
        m_display_up->clear();
        m_display_down->setText("OVERFLOW");
        overflow = true;
    }
    m_after_unary_op = true;
    digit_clicked = false;
}

void Calculator::powClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    exp_clicked = false;
    m_after_unary_op = false;
    m_after_binary_op = true;
    m_binary_op_before_equal = true;
    equal_clicked = false;
    m_double_op = "^";
    if (!digit_clicked)
    {
        m_display_up->setText(QString::number(m_display_down->text().toDouble()) + m_double_op);
    }
    else
    {
        QString upper = m_display_up->text();
        QString prev_op;
        if (!upper.isEmpty())
        {
            prev_op = upper.last(1);
            upper.chop(1);
        }
        else
        {
            m_display_up->setText(QString::number(m_display_down->text().toDouble()) + m_double_op);
            digit_clicked = false;
            return;
        }
        if (prev_op == m_plus)
        {
            m_display_down->setText(QString::number(std::pow(upper.toDouble(),m_display_down->text().toDouble())));
        }
        prev_op = m_double_op;
        if (!after_abortion)
        {
            m_display_up->setText(m_display_down->text() + m_double_op);
        }
        digit_clicked = false;
    }
}

void Calculator::logClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    exp_clicked = false;
    m_after_unary_op = false;
    m_after_binary_op = true;
    m_binary_op_before_equal = true;
    equal_clicked = false;
    m_double_op = " log base ";
    if (!digit_clicked)
    {
        m_display_up->setText(QString::number(m_display_down->text().toDouble()) + m_double_op);
    }
    else
    {
        QString upper = m_display_up->text();
        QString prev_op;
        if (!upper.isEmpty())
        {
            prev_op = upper.last(1);
            upper.chop(1);
        }
        else
        {
            m_display_up->setText(QString::number(m_display_down->text().toDouble()) + m_double_op);
            digit_clicked = false;
            return;
        }
        if (prev_op == m_plus)
        {
            m_display_down->setText(QString::number(std::log(upper.toDouble())/std::log(m_display_down->text().toDouble())));
        }
        prev_op = m_double_op;
        if (!after_abortion)
        {
            m_display_up->setText(m_display_down->text() + m_double_op);
        }
        digit_clicked = false;
    }
}

void Calculator::rootClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    exp_clicked = false;
    m_after_unary_op = false;
    m_after_binary_op = true;
    m_binary_op_before_equal = true;
    equal_clicked = false;
    m_double_op = " root ";
    if (!digit_clicked)
    {
        m_display_up->setText(QString::number(m_display_down->text().toDouble()) + m_double_op);
    }
    else
    {
        QString upper = m_display_up->text();
        QString prev_op;
        if (!upper.isEmpty())
        {
            prev_op = upper.last(1);
            upper.chop(1);
        }
        else
        {
            m_display_up->setText(QString::number(m_display_down->text().toDouble()) + m_double_op);
            digit_clicked = false;
            return;
        }
        if (prev_op == m_plus)
        {
            m_display_down->setText(QString::number(std::pow(upper.toDouble(), 1/m_display_down->text().toDouble())));
        }
        prev_op = m_double_op;
        if (!after_abortion)
        {
            m_display_up->setText(m_display_down->text() + m_double_op);
        }
        digit_clicked = false;
    }
}

void Calculator::clear()
{
    m_display_down->setText("0");
}

void Calculator::clearAll()
{
    m_after_binary_op = false;
    m_after_unary_op = false;
    m_binary_op_before_equal = false;
    after_abortion = false;
    equal_clicked = false;
    m_display_up->clear();
    m_display_down->setText("0");
}

void Calculator::clearMemory()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    m_sum_in_mem = 0.;
}

void Calculator::readMemory()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (equal_clicked)
    {
        m_display_up->clear();
        digit_clicked = true;
        equal_clicked = false;
    }
    digit_clicked = true;
    m_display_down->setText(QString::number(m_sum_in_mem));
}

void Calculator::addToMemory()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    m_sum_in_mem += m_display_down->text().toDouble();
}

void Calculator::minToMemory()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    m_sum_in_mem -= m_display_down->text().toDouble();
}

void Calculator::selectorClicked()
{
    QMenu menu("Calculator Modes", selectorButton);
    QAction* actionBasic = new QAction("Basic", &menu);
    QAction* actionAdvanced = new QAction("Advanced", &menu);
    QObject::connect(actionBasic, &QAction::triggered, [&]() {
        setStandart();
        menu.close();
        });
    QObject::connect(actionAdvanced, &QAction::triggered, [&]() {
        setAdvanced();
        menu.close();
        });
    menu.addAction(actionBasic);
    menu.addAction(actionAdvanced);
    QPoint buttonPos = selectorButton->mapToGlobal(QPoint(0, selectorButton->height()));
    menu.exec(buttonPos);
}

void Calculator::trigClicked()
{
    if (!trig_clicked)
    {
        modButton->hide();
        clearButton->hide();
        absButton->hide();
        expButton->hide();
        reciprocalButton->hide();
        factButton->hide();
        sinhButton->hide();
        coshButton->hide();
        tanhButton->hide();
        acoshButton->hide();
        asinhButton->hide();
        atanhButton->hide();
        sinButton->show();
        cosButton->show();
        tanButton->show();
        acosButton->show();
        asinButton->show();
        atanButton->show();
        hipButton -> show();
        trigonometryButton->setObjectName("specButton");
        trigonometryButton->setStyleSheet("MyButton#specButton");
        trig_clicked = true;
    }
    else
    {
        modButton->show();
        clearButton->show();
        absButton->show();
        expButton->show();
        reciprocalButton->show();
        factButton->show();
        sinButton->hide();
        cosButton->hide();
        tanButton->hide();
        acosButton->hide();
        asinButton->hide();
        atanButton->hide();
        sinhButton->hide();
        coshButton->hide();
        tanhButton->hide();
        acoshButton->hide();
        asinhButton->hide();
        atanhButton->hide();
        hipButton->hide();
        trigonometryButton->setObjectName("");
        hipButton->setObjectName("");
        trigonometryButton->setStyleSheet("MyButton");
        hipButton->setStyleSheet("MyButton");
        hip_clicked = false;
        trig_clicked = false;
    }
}

void Calculator::trigOperatorClicked()
{
    if (after_abortion or overflow)
    {
        m_display_down->setText("0");
        after_abortion = false;
        overflow = false;
        return;
    }
    if (equal_clicked)
    {
        m_binary_op_before_equal = false;
        m_display_up->clear();
    }
    double num = m_display_down->text().toDouble();
    equal_clicked = false;
    exp_clicked = false;
    MyButton* btn = qobject_cast<MyButton*>(sender());
    if (btn == nullptr)
    {
        return;
    }
    m_unary_op = btn->text();
    QString upper = m_display_up->text();
    if (m_unary_op == "sin")
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("sin" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "sin" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "sin" + m_display_down->text());
        }
        if (degRadButton->text() == "RAD")
            m_display_down->setText(QString::number(std::sin(num)));
        else
            m_display_down->setText(QString::number(std::sin(num * std::numbers::pi / 180.0)));
    }
    else if (m_unary_op == "cos")
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("cos" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "cos" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "cos" + m_display_down->text());
        }
        if (degRadButton->text() == "RAD")
            m_display_down->setText(QString::number(std::cos(num)));
        else
            m_display_down->setText(QString::number(std::cos(std::numbers::pi / 180.0)));
    }
    else if (m_unary_op == "tan")
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("tan" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "tan" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "tan" + m_display_down->text());
        }
        if (degRadButton->text() == "RAD")
            m_display_down->setText(QString::number(std::tan(num)));
        else
            m_display_down->setText(QString::number(std::tan(num * std::numbers::pi / 180.0)));
    }
    else if (m_unary_op == "sinh")
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("sinh" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "sinh" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "sinh" + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::sinh(num)));
    }
    else if (m_unary_op == "cosh")
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("cosh" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "cosh" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "cosh" + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::cosh(num)));
    }
    else if (m_unary_op == "tanh")
    {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("tanh" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "tanh" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "tanh" + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::tanh(num)));
    }
    else if (m_unary_op == "asin")
    {
        if (m_display_down->text().toDouble() > 1 and m_display_down->text().toDouble() < -1)
        {
            abortOperation();
        }
        else
        {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("asin" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "asin" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "asin" + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::asin(m_display_down->text().toDouble())));
    }
}
        else if (m_unary_op == "acos")
    {
        if (m_display_down->text().toDouble() > 1 and m_display_down->text().toDouble() < -1)
        {
            abortOperation();
        }
        else
        {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("acos" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "acos" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "acos" + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::acos(m_display_down->text().toDouble())));
    }
        }
        else if (m_unary_op == "atan")
    {
            if (m_display_down->text().toDouble() > 1 and m_display_down->text().toDouble() < -1)
            {
                abortOperation();
            }
            else
            {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("atan" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "atan" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "atan" + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::atan(m_display_down->text().toDouble())));
    }
        }
        else if (m_unary_op == "asinh")
    {
        if (m_display_down->text().toDouble() > 1 and m_display_down->text().toDouble() < -1)
        {
            abortOperation();
        }
        else
        {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("asinh" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "asinh" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "asinh" + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::asinh(m_display_down->text().toDouble())));
    }
        }
        else if (m_unary_op == "acosh")
    {
        if (m_display_down->text().toDouble() > 1 and m_display_down->text().toDouble() < -1)
        {
            abortOperation();
        }
        else
        {
        if (!m_binary_op_before_equal)
        {
            m_display_up->setText("acosh" + m_display_down->text());
        }
        else if (!digit_clicked)
        {
            bool flag = false;
            QString minus = "-";
            if (upper[0] == '-')
            {
                upper.remove(0, 1);
                flag = true;
            }
            upper = upper.split(m_double_op)[0];
            if (flag)
            {
                upper = minus + upper;
            }
            m_display_up->setText(upper + m_double_op + "acosh" + m_display_down->text());
        }
        else
        {
            m_display_up->setText(upper + "acosh" + m_display_down->text());
        }
        m_display_down->setText(QString::number(std::acosh(m_display_down->text().toDouble())));
    }
        }
        else if (m_unary_op == "atanh")
        {
            if (m_display_down->text().toDouble() > 1 and m_display_down->text().toDouble() < -1)
            {
                abortOperation();
            }
            else
            {
                if (!m_binary_op_before_equal)
                {
                    m_display_up->setText("atanh" + m_display_down->text());
                }
                else if (!digit_clicked)
                {
                    bool flag = false;
                    QString minus = "-";
                    if (upper[0] == '-')
                    {
                        upper.remove(0, 1);
                        flag = true;
                    }
                    upper = upper.split(m_double_op)[0];
                    if (flag)
                    {
                        upper = minus + upper;
                    }
                    m_display_up->setText(upper + m_double_op + "atanh" + m_display_down->text());
                }
                else
                {
                    m_display_up->setText(upper + "atanh" + m_display_down->text());
                }
                m_display_down->setText(QString::number(std::atanh(m_display_down->text().toDouble())));
            }
        }
    if (m_display_down->text() == "inf")
    {
        m_display_up->clear();
        m_display_down->setText("OVERFLOW");
        overflow = true;
    }
    m_after_unary_op = true;
    digit_clicked = false;
}


void Calculator::expClicked()
{
    if (!m_display_down->text().contains("e"))
    {
        m_display_down->setText(m_display_down->text() + "e+0");
        exp_clicked = true;
    }
}

void Calculator::sec1Clicked()
{
    if (!sec1_clicked)
    {
        squaredButton->hide();
        squareRootButton->hide();
        powButton->hide();
        tenxButton->hide();
        lgButton->hide();
        lnButton->hide();
        cubeButton->show();
        cubeRootButton->show();
        rootButton->show();
        twoxButton->show();
        logButton->show();
        exButton->show();
        sec1Button->setObjectName("specButton");
        sec1Button->setStyleSheet("MyButton#specButton");
        sec1_clicked = true;
    }
    else
    {
        cubeButton->hide();
        cubeRootButton->hide();
        rootButton->hide();
        twoxButton->hide();
        logButton->hide();
        exButton->hide();
        squaredButton->show();
        squareRootButton->show();
        powButton->show();
        tenxButton->show();
        lgButton->show();
        lnButton->show();
        sec1Button->setObjectName("");
        sec1Button->setStyleSheet("MyButton");
        sec1_clicked = false;
    }
}

void Calculator::hipClicked()
{
    if (!hip_clicked)
    {
        sinButton->hide();
        cosButton->hide();
        tanButton->hide();
        acosButton->hide();
        asinButton->hide();
        atanButton->hide();
        sinhButton->show();
        coshButton->show();
        tanhButton->show();
        acoshButton->show();
        asinhButton->show();
        atanhButton->show();
        hipButton->setObjectName("specButton");
        hipButton->setStyleSheet("MyButton#specButton");
        hip_clicked = true;
    }
    else
    {
        sinButton->show();
        cosButton->show();
        tanButton->show();
        acosButton->show();
        asinButton->show();
        atanButton->show();
        sinhButton->hide();
        coshButton->hide();
        tanhButton->hide();
        acoshButton->hide();
        asinhButton->hide();
        atanhButton->hide();
        hipButton->setObjectName("");
        hipButton->setStyleSheet("MyButton");
        hip_clicked = false;
    }
}

void Calculator::constClicked()
{
    MyButton* btn = qobject_cast<MyButton*>(sender());
    if (btn == nullptr)
    {
        return;
    }
    if (btn->text() == m_pi)
    {
        m_display_down->setText(QString::number(std::numbers::pi));
    }
    else m_display_down->setText(QString::number(std::numbers::e));
}

void Calculator::degRadClicked()
{
    if (degRadButton->text()=="DEG")
        degRadButton->setText("RAD");      
    else 
        degRadButton->setText("DEG");

}

MyButton* Calculator::createButton(const QString& text, const char* member)
{
    MyButton* btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

void Calculator::abortOperation()
{
    m_display_up->clear();
    m_display_down->setText("ERROR");
    after_abortion = true;
}

void Calculator::setStandart()
{
    clearLayout(mainLayout);
    trig_clicked = false;
    hip_clicked = false;
    sec1_clicked = false;
    degRadButton->hide();
    sec1Button->hide();
    trigonometryButton->hide();
    absButton->hide();
    modButton->hide();
    factButton->hide();
    expButton->hide();
    eButton->hide();
    piButton->hide();
    powButton->hide();
    tenxButton->hide();
    lgButton->hide();
    lnButton->hide();
    changeSignButton->hide();
    cubeButton->hide();
    cubeRootButton->hide();
    rootButton->hide();
    twoxButton->hide();
    logButton->hide();
    exButton->hide();
    sinButton->hide();
    cosButton->hide();
    tanButton->hide();
    acosButton->hide();
    asinButton->hide();
    atanButton->hide();
    coshButton->hide();
    hipButton->hide();
    sinhButton->hide();
    tanhButton->hide();
    acoshButton->hide();
    asinhButton->hide();
    atanhButton->hide();
    squaredButton->show();
    squareRootButton->show();
    reciprocalButton -> show();
    clearButton->show();
    mainLayout->addWidget(m_display_up, 1, 0, 1, 4);
    mainLayout->addWidget(m_display_down, 2, 0, 2, 4);
    mainLayout->addWidget(backspaceButton, 5, 2);
    mainLayout->addWidget(clearButton, 5, 0);
    mainLayout->addWidget(clearAllSignButton, 5, 1);
    mainLayout->addWidget(clearMemoryButton, 4, 0);
    mainLayout->addWidget(readMemoryButton, 4, 1);
    mainLayout->addWidget(addMemoryButton, 4, 2);
    mainLayout->addWidget(minToMemoryButton, 4, 3);
    for (int i = 1; i < 10; ++i)
    {
        int row = 9 - (i - 1) / 3;
        int col = (i - 1) % 3;
        mainLayout->addWidget(m_digitButtons[i], row, col);
    }
    mainLayout->addWidget(m_digitButtons[0], 10, 0, 1, 2);
    mainLayout->addWidget(pointButton, 10, 2);
    mainLayout->addWidget(equalButton, 9, 3, 2, 1);
    mainLayout->addWidget(divisionButton, 5, 3);
    mainLayout->addWidget(timesButton, 6, 3);
    mainLayout->addWidget(reciprocalButton, 6, 0);
    mainLayout->addWidget(squaredButton, 6, 1);
    mainLayout->addWidget(squareRootButton, 6, 2);
    mainLayout->addWidget(minusButton, 7, 3);
    mainLayout->addWidget(plusButton, 8, 3);
    mainLayout->addWidget(selectorButton, 0, 0);
    mainLayout->addWidget(selectorButton, 0, 0);
    setLayout(mainLayout);
    setWindowTitle("Calculator (Basic)");
};

void Calculator::setAdvanced()
{
    clearLayout(mainLayout);
    degRadButton->show();
    sec1Button->show();
    trigonometryButton->show();
    absButton->show();
    modButton->show();
    factButton->show();
    expButton->show();
    eButton->show();
    piButton->show();
    powButton->show();
    tenxButton->show();
    lgButton->show();
    lnButton->show();
    changeSignButton->show();
    mainLayout->addWidget(m_display_up, 1, 0, 1, 5);
    mainLayout->addWidget(m_display_down, 2, 0, 2, 5);
    mainLayout->addWidget(backspaceButton, 6, 4);
    mainLayout->addWidget(clearButton, 5, 3);
    mainLayout->addWidget(asinButton, 5, 3);
    mainLayout->addWidget(asinhButton, 5, 3);
    mainLayout->addWidget(clearAllSignButton, 5, 4);
    mainLayout->addWidget(clearMemoryButton, 4, 1);
    mainLayout->addWidget(readMemoryButton, 4, 2);
    mainLayout->addWidget(addMemoryButton, 4, 3);
    mainLayout->addWidget(minToMemoryButton, 4, 4);
    for (int i = 1; i < 10; ++i)
    {
        int row = 10 - (i - 1) / 3;
        int col = (i - 1) % 3 + 1;
        mainLayout->addWidget(m_digitButtons[i], row, col);
    }
    mainLayout->addWidget(m_digitButtons[0], 11, 2);
    mainLayout->addWidget(pointButton, 11, 3);
    mainLayout->addWidget(changeSignButton, 11, 1);
    mainLayout->addWidget(equalButton, 11, 4);
    mainLayout->addWidget(divisionButton, 7, 4);
    mainLayout->addWidget(timesButton, 8, 4);
    mainLayout->addWidget(reciprocalButton, 7, 2);
    mainLayout->addWidget(tanButton, 7, 2);
    mainLayout->addWidget(tanhButton, 7, 2);
    mainLayout->addWidget(squaredButton, 6, 0);
    mainLayout->addWidget(squareRootButton, 7, 0);
    mainLayout->addWidget(minusButton, 9, 4);
    mainLayout->addWidget(plusButton, 10, 4);
    mainLayout->addWidget(selectorButton, 0, 0);
    mainLayout->addWidget(degRadButton, 4, 0);
    mainLayout->addWidget(sec1Button, 5, 0);
    mainLayout->addWidget(trigonometryButton, 5, 1);
    mainLayout->addWidget(powButton, 8, 0);
    mainLayout->addWidget(tenxButton, 9, 0);
    mainLayout->addWidget(lgButton, 10, 0);
    mainLayout->addWidget(lnButton, 11, 0);
    mainLayout->addWidget(piButton, 7, 1);
    mainLayout->addWidget(eButton, 6, 1);
    mainLayout->addWidget(hipButton, 6, 1);
    mainLayout->addWidget(absButton, 6, 2);
    mainLayout->addWidget(cosButton, 6, 2);
    mainLayout->addWidget(coshButton, 6, 2);
    mainLayout->addWidget(modButton, 5, 2);
    mainLayout->addWidget(sinButton, 5, 2);
    mainLayout->addWidget(sinhButton, 5, 2);
    mainLayout->addWidget(expButton, 6, 3);
    mainLayout->addWidget(acosButton, 6, 3);
    mainLayout->addWidget(acoshButton, 6, 3);
    mainLayout->addWidget(factButton, 7, 3);
    mainLayout->addWidget(atanButton, 7, 3);
    mainLayout->addWidget(atanhButton, 7, 3);
    mainLayout->addWidget(cubeButton, 6, 0);
    mainLayout->addWidget(cubeRootButton, 7, 0);
    mainLayout->addWidget(rootButton, 8, 0);
    mainLayout->addWidget(twoxButton, 9, 0);
    mainLayout->addWidget(logButton, 10, 0);
    mainLayout->addWidget(exButton, 11, 0);
    sec1_clicked = false;
    setLayout(mainLayout);
    setWindowTitle("Calculator (Advanced)");
};

void Calculator::clearLayout(QLayout* layout)
{
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        if (QWidget* widget = item->widget())
        {
            layout->removeWidget(widget);
        }
        if (QLayout* childLayout = item->layout())
        {
            clearLayout(childLayout);
        }
        delete item;
    }
}