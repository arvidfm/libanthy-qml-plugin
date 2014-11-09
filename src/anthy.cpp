#include <QTextCodec>
#include <anthy/anthy.h>

#include "anthy.h"

Anthy::Anthy(QQuickItem *parent):
    QQuickItem(parent) {

    qDebug() << "anthy_init()";

    anthy_init();
    this->context = anthy_create_context();

    this->codec = QTextCodec::codecForName("EUC-JP");

    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
}

Anthy::~Anthy() {
    qDebug("anthy_release_context(this->context)\n");
    anthy_release_context(this->context);
    qDebug("anthy_quit()\n");
    anthy_quit();
}


void Anthy::reset() {
    qDebug("anthy_reset_context(this->context)\n");
    anthy_reset_context(this->context);
}

void Anthy::set_string(QString string) {
    QByteArray arr = this->codec->fromUnicode(string);
    qDebug().nospace() << "anthy_set_string(this->context, " << string << ")\n";
    anthy_set_string(this->context, arr.data());
}

int Anthy::segments() {
    qDebug("anthy_get_stat(this->context, &this->conv_stat)");
    anthy_get_stat(this->context, &this->conv_stat);
    qDebug(" -> %d (conv_stat.nr_segment)\n", this->conv_stat.nr_segment);
    return this->conv_stat.nr_segment;
}

int Anthy::segment_length(int i) {
    if (i < 0 || i >= this->segments()) {
        return -1;
    }
    qDebug("anthy_get_segment_stat(this->context, %d, &this->segment_stat)", i);
    anthy_get_segment_stat(this->context, i, &this->segment_stat);
    qDebug(" -> %d (segment_stat.seg_len)\n", this->segment_stat.seg_len);
    return this->segment_stat.seg_len;
}

int Anthy::segment_candidates(int i) {
    if (i < 0 || i >= this->segments()) {
        return -1;
    }
    qDebug("anthy_get_segment_stat(this->context, %d, &this->segment_stat)", i);
    anthy_get_segment_stat(this->context, i, &this->segment_stat);
    qDebug(" -> %d (segment_stat.nr_candidate)\n", this->segment_stat.nr_candidate);
    return this->segment_stat.nr_candidate;
}

QString Anthy::get_candidate(int segment, int candidate) {
    char buf[1000];
    qDebug("anthy_get_segment(this->context, %d, %d, buf, 1000)", segment, candidate);
    anthy_get_segment(this->context, segment, candidate, buf, 1000);
    qDebug().nospace() << " -> " << this->codec->toUnicode(buf) << " (buf)\n";
    return this->codec->toUnicode(buf);
}

void Anthy::commit_segment(int segment, int candidate) {
    QByteArray qba = this->get_candidate(segment, candidate).toLocal8Bit();
    qDebug("anthy_commit_segment(this->context, %d, %d)\n", segment, candidate);
    anthy_commit_segment(this->context, segment, candidate);
}

void Anthy::set_prediction_string(QString string) {
    QByteArray arr = this->codec->fromUnicode(string);
    qDebug().nospace() << "anthy_set_prediction_string(this->context, " << string << ")\n";
    anthy_set_prediction_string(this->context, arr.data());
}

int Anthy::predictions() {
    qDebug("anthy_get_prediction_stat(this->context, &this->prediction_stat)");
    anthy_get_prediction_stat(this->context, &this->prediction_stat);
    qDebug(" -> %d (prediction_stat.nr_prediction)\n", this->prediction_stat.nr_prediction);
    return this->prediction_stat.nr_prediction;
}

QString Anthy::get_prediction(int i) {
    char buf[1000];
    qDebug("anthy_get_prediction(this->context, %d, buf, 1000)", i);
    anthy_get_prediction(this->context, i, buf, 1000);
    qDebug().nospace() << " -> " << this->codec->toUnicode(buf) << " (buf)\n";
    return this->codec->toUnicode(buf);
}

void Anthy::commit_prediction(int i) {
    qDebug("anthy_commit_prediction(this->context, %d)\n", i);
    anthy_commit_prediction(this->context, i);
}

void Anthy::print_context() {
    qDebug("anthy_print_context(this->context)\n");
    anthy_print_context(this->context);
}
