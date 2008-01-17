/******************************************************************************
 *
 * Copyright (C) 1997-2008 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#ifndef DOCSETS_H
#define DOCSETS_H

#include "qtbc.h"
#include <qtextstream.h>
#include <qstrlist.h>
#include "sortdict.h"

#include "index.h"

class QFile;
class Definition;

/*! A class that generates docset files.
 *  These files can be used to create context help 
 *  for use within Apple's Xcode 3.0 development environment
 */
class DocSets  : public IndexIntf
{

  public:
    DocSets();
   ~DocSets();
    void initialize();
    void finalize();
    void incContentsDepth();
    void decContentsDepth();
    void addContentsItem(bool isDir,
                         const char *name, 
                         const char *ref = 0, 
                         const char *file = 0,
                         const char *anchor = 0
                        );
    void addIndexItem(const char *level1, const char *level2, 
                      const char *contRef, const char *memRef,
                      const char *anchor,const MemberDef *md);
    void addIndexFile(const char *name);

  private:
    void writeToken(QTextStream &t, const Definition *d,
                    const QCString &type, const QCString &lang,
                    const char *scope=0, const char *anchor=0,
                    const char *decl=0);
    struct NodeDef
    {
      NodeDef(bool d,const QCString &n,const QCString &r,
                    const QCString &f,const QCString &a,int i) :
                   isDir(d), name(n), ref(r), file(f), anchor(a),id(i) {}
      bool isDir;
      QCString name;
      QCString ref;
      QCString file;
      QCString anchor;
      int id;
    };
    QCString indent();
    QFile *m_nf;
    QFile *m_tf;
    QTextStream m_nts;
    QTextStream m_tts;
    int m_dc;
    int m_id;
    QArray<bool> m_firstNode;
    SDict<NodeDef> m_nodes;
    SDict<void> m_scopes;
};

#endif /* DOCSETS_H */

