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
package com.google.security.zynamics.binnavi.Gui.MainWindow.ProjectTree.Nodes.AddressSpace.Component.Help;



import java.net.URL;

import com.google.security.zynamics.binnavi.Help.CHelpFunctions;
import com.google.security.zynamics.binnavi.Help.IHelpInformation;


/**
 * Context-sensitive help information for fields that show the modification date of address spaces.
 */
public final class CModificationDateHelp implements IHelpInformation {
  @Override
  public String getText() {
    return "This field shows the last the time the address space was last updated.";
  }

  @Override
  public URL getUrl() {
    return CHelpFunctions.urlify(CHelpFunctions.MAIN_WINDOW_FILE);
  }
}
