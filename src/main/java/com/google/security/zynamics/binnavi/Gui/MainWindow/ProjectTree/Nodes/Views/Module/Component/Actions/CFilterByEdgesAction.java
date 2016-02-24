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
package com.google.security.zynamics.binnavi.Gui.MainWindow.ProjectTree.Nodes.Views.Module.Component.Actions;



import com.google.security.zynamics.zylib.gui.textfields.TextHelpers;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.JTextField;


/**
 * Action class for filtering views by edge count.
 */
public final class CFilterByEdgesAction extends AbstractAction {
  /**
   * Used for serialization.
   */
  private static final long serialVersionUID = 8570733381669936465L;

  /**
   * The filter field where the text is inserted.
   */
  private final JTextField m_filterField;

  /**
   * Creates a new action object.
   * 
   * @param filterField The filter field where the text is inserted.
   */
  public CFilterByEdgesAction(final JTextField filterField) {
    super("Filter by edge count");

    m_filterField = filterField;
  }

  @Override
  public void actionPerformed(final ActionEvent event) {
    TextHelpers.insert(m_filterField, "edges==0");
  }
}
