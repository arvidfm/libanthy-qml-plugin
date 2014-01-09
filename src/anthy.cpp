#include <QTextCodec>
#include <anthy/anthy.h>

#include "anthy.h"

Anthy::Anthy(QQuickItem *parent):
    QQuickItem(parent) {

    qDebug() << "Anthy started";

    anthy_init();
    this->context = anthy_create_context();

    this->codec = QTextCodec::codecForName("EUC-JP");

    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
}

Anthy::~Anthy() {
    anthy_release_context(this->context);
    anthy_quit();
}


void Anthy::reset() {
    anthy_reset_context(this->context);
}

void Anthy::set_string(QString string) {
    QByteArray arr = this->codec->fromUnicode(string);
    anthy_set_string(this->context, arr.data());
}

int Anthy::segments() {
    anthy_get_stat(this->context, &this->conv_stat);
    return this->conv_stat.nr_segment;
}

int Anthy::segment_length(int i) {
    if (i < 0 || i >= this->segments()) {
        return -1;
    }
    anthy_get_segment_stat(this->context, i, &this->segment_stat);
    return this->segment_stat.seg_len;
}

int Anthy::segment_candidates(int i) {
    if (i < 0 || i >= this->segments()) {
        return -1;
    }
    anthy_get_segment_stat(this->context, i, &this->segment_stat);
    return this->segment_stat.nr_candidate;
}

QString Anthy::get_candidate(int segment, int candidate) {
    char buf[1000];
    anthy_get_segment(this->context, segment, candidate, buf, 1000);
    return this->codec->toUnicode(buf);
}

void Anthy::commit_segment(int segment, int candidate) {
    printf("Commiting segment %d, candidate %d in anthy\n", segment, candidate);
    printf("Context is %p\n", this->context);
    printf("Number of candidates is %d\n", this->segment_candidates(segment));
    anthy_commit_segment(this->context, segment, candidate);
    printf("Successfully commited\n");
}

void Anthy::set_prediction_string(QString string) {
    QByteArray arr = this->codec->fromUnicode(string);
    anthy_set_prediction_string(this->context, arr.data());
}

int Anthy::predictions() {
    anthy_get_prediction_stat(this->context, &this->prediction_stat);
    return this->prediction_stat.nr_prediction;
}

QString Anthy::get_prediction(int i) {
    char buf[1000];
    anthy_get_prediction(this->context, i, buf, 1000);
    return this->codec->toUnicode(buf);
}

void Anthy::commit_prediction(int i) {
    anthy_commit_prediction(this->context, i);
}

void Anthy::print_context() {
    anthy_print_context(this->context);
}
