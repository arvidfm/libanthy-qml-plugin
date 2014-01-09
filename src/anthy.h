#ifndef ANTHY_H
#define ANTHY_H

#include <QQuickItem>
#include <QString>
#include <QTextCodec>

#include <anthy/anthy.h>

class Anthy : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Anthy)
    //Q_PROPERTY(int value READ myFunction)
private:
    anthy_context_t context;
    struct anthy_conv_stat conv_stat;
    struct anthy_segment_stat segment_stat;
    struct anthy_prediction_stat prediction_stat;
    QTextCodec *codec;
public:
    Anthy(QQuickItem *parent = 0);
    ~Anthy();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void set_string(QString string);
    Q_INVOKABLE int segments();
    Q_INVOKABLE int segment_length(int i);
    Q_INVOKABLE int segment_candidates(int i);
    Q_INVOKABLE QString get_candidate(int segment, int candidate);
    Q_INVOKABLE void commit_segment(int segment, int candidate);
    Q_INVOKABLE void set_prediction_string(QString string);
    Q_INVOKABLE int predictions();
    Q_INVOKABLE QString get_prediction(int i);
    Q_INVOKABLE void commit_prediction(int i);
    Q_INVOKABLE void print_context();
};

#endif // ANTHY_H

