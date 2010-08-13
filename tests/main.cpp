/**
  * TwitOAvis
  * Copyright (c) 2010 arturo182 <arturo182@tlen.pl>
  * All rights reserved
  *
  * $Id$
  */

#include "TwitOAvis.h"

#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TwitOAvis *lib = new TwitOAvis("vP69u6PGSakKTIoE2ApvVw", "g2PjaAttF0prUfmMTSlzVe9Dr7LBqCGcJXlWwhlwA");

    return a.exec();
}
