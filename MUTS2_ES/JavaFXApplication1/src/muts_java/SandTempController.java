/*
MUTS Java Sand Temperature Controller
Author: Derek Chase Brown
Copyright (c) 2017
Java program which provides functionality to the FXML document regarding sand
temperature chart monitoring.
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

import java.io.File;
import java.io.FileNotFoundException;
import java.net.URL;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.Scanner;
import java.util.prefs.Preferences;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListView;

/**
 * FXML Controller class
 *
 * @author derek
 */
public class SandTempController implements Initializable {
    @FXML
    private DatePicker datePickSandFilter;
    @FXML
    private ListView areaList;
    @FXML
    private LineChart<String,Number> SANDTEMP;
    @FXML
    private NumberAxis SandTempyAxis;
    @FXML
    private CategoryAxis SandTempxAxis;
    
    private String DataDirectory = "";
    private final List<String> results = new ArrayList<>();
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
        populateDataField(null);
        
        // set Sand temp x axis properties
        SandTempxAxis.setAutoRanging(true);
        SandTempxAxis.setTickLabelFont(new javafx.scene.text.Font("System",18));
        SandTempxAxis.setLabel(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TIME"));
        // set Sand temp y axis range properties
        SandTempyAxis.setTickLabelFont(new javafx.scene.text.Font("System",14));
        SandTempyAxis.setAutoRanging(false);
        SandTempyAxis.setLowerBound(0);
        SandTempyAxis.setTickUnit(1);
        SandTempyAxis.setUpperBound(45);
        SandTempyAxis.setLabel(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TEMPERATURE"));
    }
    
    public SandTempController() 
    {
        Preferences pref;
        pref = Preferences.userRoot().node(FXMLDocumentController.class.getName());
        this.DataDirectory = pref.get("DataDirectory", "NIL");
    }
        
    @FXML
    public void handleDateChange()
    {
        populateDataField(datePickSandFilter.getValue());
    }
    

     
    @FXML
    public void handleDataSandFile() throws FileNotFoundException
    {
        System.out.println("You clicked me!");
        double[] temps = new double[3]; // array for storing temperature from clusters
        double minVal = Double.MAX_VALUE;  // The minimum values for each of the three temp measurements of sand
        double maxVal = Double.MIN_VALUE;  // the max values for each of the three temp measurements of sand.

        String filename = DataDirectory + '\\' + results.get(areaList.getSelectionModel().getSelectedIndex());


        File inputfile = new File(filename + ".csv"); //open file for reading
        Scanner sc = new Scanner(inputfile);
        sc.useDelimiter(",|\\n");

        String time = sc.next(); // the first data point should be the time.
        String countryCode = sc.next();
        String terminalNum = sc.next();
        String clusterNum = sc.next();


        SANDTEMP.titleProperty().set(java.text.MessageFormat.format(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SAND TEMPERATURE DATA FOR TERMINALAREA"), new Object[] {terminalNum, clusterNum}));
        SANDTEMP.setCreateSymbols(false);

        XYChart.Series temphighseries = new XYChart.Series<>();
        XYChart.Series tempmidseries = new XYChart.Series<>();
        XYChart.Series templowseries = new XYChart.Series<>();

        // read data from file //
        while(sc.hasNext()){

            for(int i = 0; i < 3 && sc.hasNext(); i++){ // checking hasNext twice to ensure there is still data to read.
                temps[i] = Double.parseDouble(sc.next());

                if(temps[i]/100.0 < minVal){ // setting min and max values.
                    minVal = temps[i]/100.0; // set new min
                } else if(temps[i]/100.0 >= maxVal){
                    maxVal = temps[i]/100.0; // set new max
                }

            }

            // temps are divided by 100 because sensors record floating point values
            // into short values by multiplying them by 100, keeping a reasonable precision
            // while saving space on the hardware that would otherwise be lost if 
            // floats were used.
            temphighseries.getData().add(new XYChart.Data<>(time, temps[0]/100.0));
            tempmidseries.getData().add(new XYChart.Data<>(time, temps[1]/100.0));
            templowseries.getData().add(new XYChart.Data<>(time, temps[2]/100.0));

            sc.next(); // drop date
            if(sc.hasNext()) { // if there is another line after the \n, keep reading
                time = sc.next();
                sc.next(); sc.next(); sc.next(); // toss codes
            }
        }

        sc.close(); // close scanner out

        // set series legend names //
        temphighseries.setName(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SHALLOW"));
        tempmidseries.setName(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MEDIUM DEPTH"));
        templowseries.setName(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("DEEP"));

        SANDTEMP.getData().clear();
        
        // set data with series //
        SANDTEMP.getData().add(temphighseries);
        SANDTEMP.getData().add(tempmidseries);
        SANDTEMP.getData().add(templowseries);


        // Set boundaries for sand temp y-axis //
        SandTempyAxis.setLowerBound(minVal-2);
        SandTempyAxis.setUpperBound(maxVal+2);
    }    

    private void populateDataField(LocalDate date) {
        // files should be named: S_MMDDYYYY_XXXYYYZZ.csv
        areaList.getItems().clear(); // remove all current list items
        results.clear();
        List<String> removedresults = new ArrayList<>();
        String filename;
        String tempField;
        File[] files = new File(DataDirectory).listFiles();

        if (files != null) {
            for (File file : files) {
                if (file.isFile()) {
                    filename = file.getName();
                    if (filename.endsWith(".csv") && filename.startsWith("S_")){ 
                        results.add(filename.substring(0, filename.length() - 4));
                    }
                }
            }

            if(date != null) { // if filter by date
                for (String logitem : results) {
                    if (Integer.parseInt(logitem.substring(2, 4)) != date.getMonthValue() ||
                        Integer.parseInt(logitem.substring(4, 6)) != date.getDayOfMonth() ||
                        Integer.parseInt(logitem.substring(6, 10)) != date.getYear() ) {
                            removedresults.add(logitem);     
                    }
                }
            }




            results.removeAll(removedresults);
            removedresults.clear();

            //removedresults are those files that are in the Data directory, but not used.
            // they are set-subtracted from results. We then clear removedresults, and will
            // re-use it for a different purpose in the following for loop. In this loop,
            // we take from results the raw file names, and create readable labels that
            // will populate the data field. We will store this in the recycled removedresults list.
            // This allows us to have a parallel list to results, which is global, so that when
            // the user selects from the datalist the data they want to view, all we have
            // to do to get the filename to read the data from is get the index of
            // the selected item in dataList and use it to index the results list
            // for the filename we need.
            for (String result : results) {
                String terminal = String.valueOf(Integer.parseInt(result.substring(14,17)));
                String cluster = String.valueOf(Integer.parseInt(result.substring(17,19)));
                tempField = result.substring(2,4) + '/' + result.substring(4,6) + '/' +  result.substring(6,10);
                tempField += "--Ter " + terminal;
                tempField += "--Area " + cluster;
                removedresults.add(tempField);
            }
            
            areaList.getItems().addAll(removedresults);
        }
    }
       
}
