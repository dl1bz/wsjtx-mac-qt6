#ifndef DECODE_LABEL_H
#define DECODE_LABEL_H

#include <QString>
#include <QtGlobal>

// One decoded-callsign label drawn on top of the WideGraph waterfall
// at its audio-offset x-position. WideGraph maintains a list of these
// (refreshed each time mainwindow taps the decode-append path); CPlotter
// reads the list via setDecodeLabels() and overlays them in paintEvent.
//
// Lives in its own header so widegraph.h and plotter.h can both include
// it without creating a circular dependency between the two larger
// headers.
struct DecodeLabel {
  double  freq_khz;       // audio offset (kHz), straight from the decode line
  QString callsign;       // sender's call extracted from the message field
  qint64  last_seen_ms;   // wall-clock of most recent fresh decode
  int     hits;           // for tie-breaking when stacking

  // C++11 explicit ctor (gnu++11 mode in this build doesn't accept
  // QList::append({...}) brace-enclosed init lists).
  DecodeLabel(double f, const QString& c, qint64 t, int h)
    : freq_khz(f), callsign(c), last_seen_ms(t), hits(h) {}
  DecodeLabel() : freq_khz(0), last_seen_ms(0), hits(0) {}
};

// Font-size choice for the callsign overlay. Menu values:
//   7 pt  = Small   (tightest packing, hardest to read at distance)
//   8 pt  = Normal  (default — fits dense bands, still legible)
//   10 pt = Medium  (more readable, more stacking pressure)
//   12 pt = Large   (easiest to read, biggest stacking pressure)
enum class DecodeLabelFontSize {
  Small  = 7,
  Normal = 8,
  Medium = 10,
  Large  = 12,
};

// Where to anchor the callsign overlay on the upper waterfall.
//   Top    = stack down from the top edge of the upper waterfall
//            (legacy behaviour; labels can obscure the strongest
//            signals which sit at the top of recent history)
//   Bottom = stack up from the bottom edge of the upper waterfall
//            (just above the divider) — keeps recent signal traces
//            visible and pushes labels into the older / faded area
enum class DecodeLabelPosition {
  Top    = 0,
  Bottom = 1,
};

#endif // DECODE_LABEL_H
