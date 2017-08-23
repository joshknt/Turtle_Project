/*
MUTS Java Function Library
Author: Derek Chase Brown
Copyright (c) 2017
A class of useful backend functions with no relation to the front end.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package muts_java;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

/**
 *
 * @author derek
 */
public final class MUTSLibrary {
    
    static StopStartFrameStatus showStatus(String text, boolean isRestart){
        StopStartFrameStatus awindow;
        if(isRestart){
            awindow = new StopStartFrameStatus(text,true);
        }
        else{
            awindow = new StopStartFrameStatus(text);
        }
        awindow.pack();
        awindow.setDefaultCloseOperation(1);
        awindow.setLocationRelativeTo(null);
        awindow.setDefaultCloseOperation(StopStartFrameStatus.DISPOSE_ON_CLOSE);
        awindow.setVisible(true);
        awindow.setAlwaysOnTop(true);
        awindow.requestFocus();
        return awindow;
    }

    /* *************************************************************************
    * Function used to start or stop the MUTS .NET service application in the background.
    * The function will start the service if start = true.
    ***************************************************************************/
    @SuppressWarnings("SleepWhileInLoop")
    static boolean start_stopService(boolean start, String direct, boolean isRestart)
    {
        StopStartFrameStatus window;
        String command = "stop";
        
        ProcessBuilder pb = new ProcessBuilder("cmd.exe", "/c", "sc stop","MUTSService");
        if(start){
            command = "start";
            pb = new ProcessBuilder("cmd.exe", "/c", "sc start","MUTSService",direct);
        }
        if(isRestart){
            window = showStatus(String.format(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("ATTEMPTINGTO_MUTSMONITORINGSERVICE..."), command),true); 
        }
        else{
            window = showStatus(String.format(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("ATTEMPTINGTO_MUTSMONITORINGSERVICE..."), command),false); 
        }
                
        try {
            
            Process serviceprocess = pb.start();

            
            try {
                serviceprocess.waitFor();
            } catch (InterruptedException ex) {
                Logger.getLogger(MUTSLibrary.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            InputStream inputStream = serviceprocess.getInputStream();
            InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
            BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
            String line;
            while ((line = bufferedReader.readLine()) != null) {
               System.out.println(line);
            }
        } catch (IOException ex) {
            //TODO: Check the calling thread to see if it is a swing thread or a 
            // fx thread. The two cannot run in the other, do so will cause the
            // other to become unresponsive. This exception shouldn't happen often
            // but should be fixed to show the appropriate message based on the thread.
            JFrame frame = new JFrame();
            JOptionPane.showMessageDialog(frame,
                    String.format(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MUTS SERVICE FAILED TO _ERR100"), command)
                ,
                java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SERVICEERROR"),
                JOptionPane.ERROR_MESSAGE);
            return false;
        }

        int status = getServiceState("MUTSService");
        
        // we have to wait for service to stop or start. This loop waits through
        // the pending stage.
        for(int i = 8; i >0 &&(status == 3 || status == 2); i--){
            try {
                Thread.sleep(1000); // safe, due to countdown. Loop only happens at most 8 times.
            } catch (InterruptedException ex) {
                Logger.getLogger(MUTSLibrary.class.getName()).log(Level.SEVERE, null, ex);
            }
            status = getServiceState("MUTSService");
        }
        window.dispose();

        return (start == true && getServiceState("MUTSService") == 1) ||
                (start == false && getServiceState("MUTSService") == 4); 
    }
    
    /* *************************************************************************
    * Function used to return the current running status of a service.
    * Returns: 1 if service by the argument name "service" is running, 0 if not.
    ***************************************************************************/
    static int getServiceState(String service){
        // run a service command query on the given service //
        int returnstat = -1;
        ProcessBuilder pb = new ProcessBuilder("cmd.exe", "/c", "sc query",service);
        String line = "";     
        try {

            Process serviceprocess = pb.start();

            InputStream inputStream = serviceprocess.getInputStream();
            InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
            BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
            
            
            while ((line = bufferedReader.readLine()) != null) {
                if(line.trim().startsWith("STATE"))
                    break;
            }
        } catch (IOException ex) {
            System.out.print(ex.getMessage());
        }
        if(line != null){
            String[] status = line.trim().split(" ");
            switch(status[status.length-1]){
                case "RUNNING": returnstat = 1; break;
                case "START_PENDING": returnstat = 2; break;
                case "STOP_PENDING": returnstat = 3; break;
                case "STOPPED": returnstat = 4; break;
                default: returnstat = 0;
            }

        }
        return returnstat;
    }
    

}
