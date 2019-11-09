#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QString>
#include <utility>
#include <vector>

namespace Student{

class myLabel : public QLabel
{

public:

    /**
     * @brief myLabel Constructor.
     * @param parent Parent widget
     */
    explicit myLabel(QWidget * parent = nullptr);

    /**
     * @brief addText Adds text in to the label. Shows 7 rows of text.
     * @param text Text to add.
     */
    void addText(std::string text);

private:

    std::vector<std::string> textRows_ = {"","","","","","",""};
};
}

#endif // MYLABEL_H
