/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#ifndef CTKTRACKEDPLUGIN_P_H
#define CTKTRACKEDPLUGIN_P_H

#include <QSharedPointer>

#include "ctkPluginAbstractTracked_p.h"
#include "ctkPluginEvent.h"

class ctkPluginTracker;
class ctkPluginTrackerCustomizer;

class ctkTrackedPlugin : public QObject,
    public ctkPluginAbstractTracked<QSharedPointer<ctkPlugin>, ctkPluginEvent>
{
  Q_OBJECT

public:
  ctkTrackedPlugin(ctkPluginTracker* pluginTracker,
                   ctkPluginTrackerCustomizer* customizer);

private slots:

  /**
   * Slot for the <code>ctkPluginTracker</code>
   * class. This method must NOT be synchronized to avoid deadlock
   * potential.
   *
   * @param event <code>ctkPluginEvent</code> object from the framework.
   */
  void pluginChanged(const ctkPluginEvent& event);

private:

  typedef ctkPluginAbstractTracked<QSharedPointer<ctkPlugin>, ctkPluginEvent> Superclass;

  ctkPluginTracker* pluginTracker;
  ctkPluginTrackerCustomizer* customizer;

  /**
   * Call the specific customizer adding method. This method must not be
   * called while synchronized on this object.
   *
   * @param item Item to be tracked.
   * @param related Action related object.
   * @return Customized object for the tracked item or <code>null</code>
   *         if the item is not to be tracked.
   */
  QVariant customizerAdding(QSharedPointer<ctkPlugin> item,
                            ctkPluginEvent related);

  /**
   * Call the specific customizer modified method. This method must not be
   * called while synchronized on this object.
   *
   * @param item Tracked item.
   * @param related Action related object.
   * @param object Customized object for the tracked item.
   */
  void customizerModified(QSharedPointer<ctkPlugin> item,
                          ctkPluginEvent related, QVariant object);

  /**
   * Call the specific customizer removed method. This method must not be
   * called while synchronized on this object.
   *
   * @param item Tracked item.
   * @param related Action related object.
   * @param object Customized object for the tracked item.
   */
  void customizerRemoved(QSharedPointer<ctkPlugin> item,
                         ctkPluginEvent related, QVariant object);
};

#endif // CTKTRACKEDPLUGIN_P_H
