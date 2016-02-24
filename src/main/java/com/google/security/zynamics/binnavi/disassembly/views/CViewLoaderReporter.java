/*
Copyright 2011-2016 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
package com.google.security.zynamics.binnavi.disassembly.views;

import com.google.security.zynamics.binnavi.Database.DefaultDatabaseLoadProgressReporter;
import com.google.security.zynamics.zylib.general.ListenerProvider;



/**
 * Used to report progress during view loading.
 */
public final class CViewLoaderReporter extends DefaultDatabaseLoadProgressReporter<ViewLoadEvents> {
  /**
   * Listeners to be notified.
   */
  private final ListenerProvider<INaviViewListener> m_listeners;

  /**
   * Creates a new reporter object.
   * 
   * @param listeners Listeners to be notified.
   */
  public CViewLoaderReporter(final ListenerProvider<INaviViewListener> listeners) {
    m_listeners = listeners;
  }

  @Override
  protected boolean report(final ViewLoadEvents event, final int counter) {
    boolean cont = true;

    for (final INaviViewListener listener : m_listeners) {
      cont &= listener.loading(event, counter);
    }

    return cont;
  }
}
