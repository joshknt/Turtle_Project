/*
MUTS Java Primary Form Controller
Author: Derek Chase Brown
Copyright (c) 2017
Java program which provides functionality to the primary FXML document.

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
import java.io.IOException;
import java.net.URL;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.Scanner;
import java.util.prefs.Preferences;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.print.PageLayout;
import javafx.print.PageOrientation;
import javafx.print.Paper;
import javafx.print.Printer;
import javafx.print.PrinterAttributes;
import javafx.print.PrinterJob;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Label;
import javafx.scene.control.Tab;
import javafx.scene.text.Text;
import javafx.stage.Stage;



/**
 *
 * @author Derek Brown
 */

public class FXMLDocumentController implements Initializable {
    ////////////////////////////////////////////////////////////////////////////
    // Standard Variables
    ////////////////////////////////////////////////////////////////////////////
    private String DataDirectory;
    private final List<String> results = new ArrayList<>();
    private final Preferences pref;
    private final long TIMERINTERVAL = 60000; // Interval in millis at which the Timer will tick.
    java.util.Timer primaryTimer; 
    java.util.TimerTask update; // tasks needed to properly update the GUI after a period of time.

    
    ////////////////////////////////////////////////////////////////////////////
    // FXML control variables
    ////////////////////////////////////////////////////////////////////////////
    @FXML
    private Label label;
    @FXML
    private Text labelMeasurements;
    @FXML
    private Text labelFilters;
    @FXML
    private Text labelDate;
    @FXML
    private Text labelTerm;
    @FXML
    private Text labelSens;
    @FXML
    private Text labelDateTermSens;
    @FXML
    private Text labelEquipment;
    @FXML
    private Text labelSettings;
    @FXML
    private Text labelEnvironment;
    @FXML
    private Text labelDataFold;
    @FXML
    private Label currentAvgSandTempLabel;
    @FXML
    private Label TEMPShallowlabel;
    @FXML
    private Label TEMPMidlabel;
    @FXML
    private Label TEMPDeeplabel;
    @FXML
    private Label TEMPShallowlabelText;
    @FXML
    private Label TEMPMidlabelText;
    @FXML
    private Label TEMPDeeplabelText;
    @FXML
    private javafx.scene.control.DatePicker datePickFilter;
    @FXML
    private javafx.scene.control.ComboBox terminalSelector, sensorSelector;
    @FXML
    private javafx.scene.control.ListView dataList;
    @FXML
    private LineChart<String,Number> TEMP;
    @FXML
    private LineChart<String,Number> MOTION;
    @FXML
    private LineChart<String,Number> HUMIDITY;
    @FXML
    private NumberAxis MotionyAxis;
    @FXML
    private CategoryAxis MotionxAxis;
    @FXML
    private NumberAxis TempyAxis;
    @FXML
    private CategoryAxis TempxAxis;
    @FXML
    private NumberAxis HumidityYAxis;
    @FXML
    private CategoryAxis HumidityXAxis;
    @FXML
    private javafx.scene.control.TabPane graphTabs;
    @FXML
    private javafx.scene.control.TextField dataTextField;
    @FXML
    private javafx.scene.control.Button serviceControlButton;
    @FXML
    private javafx.scene.control.Button sandButton;
    @FXML
    private Tab MotionTab;
    @FXML
    private Tab TempTab;
    @FXML
    private Tab HumidTab;
    @FXML
    private javafx.scene.control.MenuItem changedataloc;
    @FXML
    private javafx.scene.control.Menu settingsmenu;
    @FXML
    javafx.scene.control.Menu Helpmenu;

    
    ////////////////////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////////////////////
    
    /* *************************************************************************
    * PrimaryController constructor.
    ***************************************************************************/
    public FXMLDocumentController() {

        this.update = new java.util.TimerTask(){
            @Override
            public void run(){
                Platform.runLater(() -> {
                    try 
                    {
                        updateSandTempLabel(); 
                        handleDateTermSenseChange(null);
                        updateServiceStatus();
                    } catch (FileNotFoundException ex) {}
                });
            }
        };
        primaryTimer = new java.util.Timer();
        primaryTimer.scheduleAtFixedRate(update, 5000, TIMERINTERVAL);
        
        
        pref = Preferences.userRoot().node(this.getClass().getName());
        this.DataDirectory = pref.get("DataDirectory", "NIL");
        
        System.out.println(DataDirectory); 
        

    }
    
    /* *************************************************************************
    * The required initialize function which sets all Axis and performs an initial
    * attempt to populate the datalist field with all available data items found.
    * Run at the start of this form.
    ***************************************************************************/
    @Override
    public void initialize(URL url, ResourceBundle rb) {
      // startService();
        populateDataField(null,-1,-1);
        
        // set motion y axis range properties
        MotionyAxis.setAutoRanging(false);
        MotionyAxis.setLowerBound(-5);
        MotionyAxis.setTickUnit(5);
        MotionyAxis.setUpperBound(18);
        MotionyAxis.setLabel(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MOVEMENTINTENSITY"));
        // set motion x axis properties
        MotionxAxis.setAutoRanging(true);
        MotionxAxis.setTickLabelFont(new javafx.scene.text.Font("System",14));
        MotionxAxis.setLabel(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TIME"));
        // set temp x axis properties
        TempxAxis.setAutoRanging(true);
        TempxAxis.setTickLabelFont(new javafx.scene.text.Font("System",14));
        TempxAxis.setLabel(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TIME"));
        // set temp y axis range properties
        TempyAxis.setTickLabelFont(new javafx.scene.text.Font("System",14));
        TempyAxis.setAutoRanging(false);
        TempyAxis.setLowerBound(0);
        TempyAxis.setTickUnit(1);
        TempyAxis.setUpperBound(45);
        TempyAxis.setLabel(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TEMPERATURE"));
      
        
        // set humidity y axis range properties
        HumidityYAxis.setAutoRanging(false);
        HumidityYAxis.setLowerBound(0);
        HumidityYAxis.setTickUnit(10);
        HumidityYAxis.setUpperBound(100);
        HumidityYAxis.setLabel(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("HUMIDITYLEVEL"));
        // set humidity x axis properties
        HumidityXAxis.setAutoRanging(true);
        HumidityXAxis.setTickLabelFont(new javafx.scene.text.Font("System",14));
        HumidityXAxis.setLabel(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TIME"));

        dataTextField.setText(this.DataDirectory);
        labelMeasurements.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MEASUREMENTS"));
        labelFilters.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("FILTERS"));
        labelDate.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("DATE"));
        labelTerm.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TERMINAL NUMBER"));
        labelSens.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SENSOR NUMBER"));
        labelDateTermSens.setText("Date -- Terminal -- Sensor");
        labelEquipment.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("EQUIPMENT"));
        labelSettings.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SETTINGS"));
        labelEnvironment.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("ENVIRONMENT"));
        currentAvgSandTempLabel.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("CURRENT AVERAGE SAND TEMPERATURE:"));
        labelDataFold.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("DATA FOLDER LOCATION"));
        TEMPShallowlabelText.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TOP"));
        TEMPMidlabelText.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MID"));
        TEMPDeeplabelText.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("DEEP"));
        sandButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SAND HISTORY"));
        MotionTab.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MOTION"));
        TempTab.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TEMPERATURE_nocel"));
        HumidTab.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("HUMIDITY"));
        changedataloc.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("CHANGE/SET DATA TRANSFER LOCATION"));
        settingsmenu.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SETTINGS"));
        Helpmenu.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("HELP"));
        
        
    }
    
    /* *************************************************************************
    * Test button. This will be removed later.
    ***************************************************************************/
    @FXML
    private void handleButtonAction(ActionEvent event) {
        System.out.println("You clicked me!");
        label.setText("Hello World!");
    }
    
    
    /* *************************************************************************
    * Function call that toggles the MUTSService running state.
    ***************************************************************************/
    @FXML
    private void handleServiceSwitchButton(ActionEvent event) {
        int serviceStatus = MUTSLibrary.getServiceState("MUTSService");
        if(serviceStatus == 1){
            serviceControlButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("ATTEMPTINGTOSTOPMONITORING"));
            if(MUTSLibrary.start_stopService(false, null,false)){
                serviceControlButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MONITORINGISOFF."));
            }else{
                Alert alert = new Alert(AlertType.ERROR);
                alert.setTitle(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SERVICEERROR"));
                alert.setHeaderText(null);
                alert.setContentText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("FAILTOSTOPERR101"));

                alert.showAndWait();            
                serviceControlButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MONITORINGISON"));
            }
                
        } else{
            serviceControlButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("ATTEMPTINGTOSTARTMONITORING"));
            if(MUTSLibrary.start_stopService(true,pref.get("XferDataDirectory","NIL"),false)){ //TODO CHANGE NIL TO DEFAULT
                serviceControlButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MONITORINGISON"));
            }
            else
            {
                serviceControlButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MONITORINGISOFF."));
            
                Alert alert = new Alert(AlertType.ERROR);
                alert.setTitle(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SERVICEERROR"));
                alert.setHeaderText(null);
                alert.setContentText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("ERROR100"));

                alert.showAndWait();
            }
        }
        
        
    }
    
    /* *************************************************************************
    * A simple handler function for the working data folder directory selection
    * menu. This is run when the user attempts to change the working directory
    * for data. Note that this is not the same as changing the directory which
    * MUTSService uses to store data to that is incoming from transmission. This
    * is done through the settings menubar item. Thus the working directory is only
    * ever changed if the user desires to read charts from other file locations.
    ***************************************************************************/
    @FXML
    private void handleFolderSelection(ActionEvent event) {
        javafx.stage.DirectoryChooser chooser = new javafx.stage.DirectoryChooser(); 
        chooser.setTitle(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SELECTDATAFOLDER"));
        File file = chooser.showDialog(null);
        if(file!=null){
            dataTextField.setText(file.getPath());
            DataDirectory = file.getPath();
            pref.put("DataDirectory", DataDirectory); // update preferences
            populateDataField(null,-1,-1); // show all with no filters
        }
    }
    
    /* *************************************************************************
    * Function that handles graph printing.
    * Not yet completed.
    ***************************************************************************/
    @FXML
    private void handlePrintGraph(ActionEvent event) {
        // TODO: complete this function so that it prints the graph, and the raw
        // data associated with it, cleanly on one page. 
        System.out.println("Printing Requested.");
        PrinterJob pj = PrinterJob.createPrinterJob();
        graphTabs.prefHeightProperty().set(400);
        graphTabs.prefWidthProperty().set(500);
        Node toPrint = graphTabs.getTabs().get(0).getContent();
        Printer printer = Printer.getDefaultPrinter();
        PageLayout pageLayout = printer.createPageLayout(Paper.A4, PageOrientation.PORTRAIT, Printer.MarginType.HARDWARE_MINIMUM);
        PrinterAttributes attr = printer.getPrinterAttributes();
        double scaleX = pageLayout.getPrintableWidth() / toPrint.getBoundsInParent().getWidth();
        double scaleY = pageLayout.getPrintableHeight() / toPrint.getBoundsInParent().getHeight();



        if (pj != null) {
            boolean success = pj.printPage(toPrint);
            if (success) {
                pj.endJob();
            } 
        }  
    }
    
    /* *************************************************************************
    * Updates the data field based on the new selected date in the filters.
    ***************************************************************************/
    @FXML
    private void handleDateTermSenseChange(ActionEvent event) {
        System.out.println("Filters Updated.");
        
        int terminal = -1;
        int sensor = -1;
        if((String)terminalSelector.getValue() != null)
            terminal = Integer.parseInt((String)terminalSelector.getValue());
        if((String)sensorSelector.getValue() != null)
            sensor = Integer.parseInt((String)sensorSelector.getValue());

        populateDataField(datePickFilter.getValue(),terminal,sensor);
    }
    
    /* *************************************************************************
    * Function that cleans any existing data off of the LineChart controls. Should
    * be run before each update to the charts.
    ***************************************************************************/
    @FXML
    private void clearCharts(){
        MOTION.getData().clear();
        TEMP.getData().clear();
        HUMIDITY.getData().clear();
    }
    
    /* *************************************************************************
    * Function which updates the title and symbol properties of a LineChart control 
    * with a given terminal number and sensor number. These arguments should be 
    * converted to string.
    ***************************************************************************/
    @FXML
    private void setChartProperties(String terminalNum, String sensorNum){
        MOTION.titleProperty().set(java.text.MessageFormat.format(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MOTION DATA FOR TERMINALSENSOR"), new Object[] {terminalNum, sensorNum}));
        TEMP.titleProperty().set(java.text.MessageFormat.format(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TEMPERATURE DATA FOR TERMINALSENSOR"), new Object[] {terminalNum, sensorNum}));
        HUMIDITY.titleProperty().set(java.text.MessageFormat.format(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("HUMIDITY DATA FOR TERMINALSENSOR"), new Object[] {terminalNum, sensorNum}));
        
        // Remove dotted nodes //
        MOTION.setCreateSymbols(false);
        TEMP.setCreateSymbols(false);
        HUMIDITY.setCreateSymbols(false);
        
    }
    
    /* *************************************************************************
    * This function charts the data of the user-selected index of the data list.
    * It then populates the temperature, motion, and humidity tabs with this data.
    ***************************************************************************/
    @FXML
    private void handleDataFileChosen(Event event) throws FileNotFoundException 
    {
        /* 
           First, we check the selected index of the list of data items to ensure
           the user has selected an actual item and not simply clicked in a blank
           area within the control. Note that this function is called when the user
           clicks anywhere within the dataList control, thus this if statement is
           a safe check on user input. 
        */
        if(dataList.getSelectionModel().getSelectedIndex() >= 0)
        {
            String time;
            ArrayList<String[]> recordArray = new ArrayList();
            clearCharts(); // Remove preexisting graphed data, if any // 
            String filename = DataDirectory + '/' + results.get(dataList.getSelectionModel().getSelectedIndex());
            
            double[] vals = new double[5]; /* array for storing values for each graph. The five
                                            elements represent, in an order determined by while loop below,
                                            temperature, and x,y, and z motion data, and humidity.*/
            
            /* The following two values represent the minimal and maximal values 
               of temperature recorded in the data file we are investigating. This
               is done so a proper y-range may be set on the graph to focus on the data
               alone and keep the graph aesthetically pleasing. */
            double minVal = Double.MAX_VALUE; // Minimal temperature
            double maxVal = Double.MIN_VALUE; // Maximal temperature

            File inputfile = new File(filename + ".csv"); //open file for reading
            try (Scanner sc = new Scanner(inputfile)) {
                sc.useDelimiter("\n"); // Records are delimited by the newline
                // First, read all records into the array list //
                while (sc.hasNext()) {
                    recordArray.add(sc.next().split(","));
                }
                sc.close();// close file
            } // Records are delimited by the newline
            
            // Now, clean the records by removing bad records //
            for(int i = 0; i < recordArray.size(); i++){
                if(recordArray.get(i).length != 10){
                    recordArray.remove(i);
                    i--;
                } 
            }
            
            // obtain chart metadata //
            String countryCode = recordArray.get(0)[1];
            String terminalNum = recordArray.get(0)[2];
            String sensorNum = recordArray.get(0)[3];


            setChartProperties(terminalNum,sensorNum);

            // The series are initialized and data is added to them. At the end of this call, they are
            // used to populate the graphs with data.
            XYChart.Series motionseriesX = new XYChart.Series<>();
            XYChart.Series motionseriesY = new XYChart.Series<>();
            XYChart.Series motionseriesZ = new XYChart.Series<>();
            XYChart.Series tempseries = new XYChart.Series<>();
            XYChart.Series humidityseries = new XYChart.Series<>();
            
            // process all records.
            for(String[] record : recordArray){
                try{
                    time = record[0]; // obtain time.
                    for(int i = 0; i < 5 ; i++){ 
                        vals[i] = Double.parseDouble(record[i+4]); //offset record by four

                        if(i == 0 && vals[i]/100.0 < minVal){ // setting min and max values.
                            minVal = vals[i]/100.0; // set new min
                        } else if(i ==0 && vals[i]/100.0 >= maxVal){
                            maxVal = vals[i]/100.0; // set new max
                        }

                    }

                    // temps are divided by 100 because sensors record floating point values
                    // into short values by multiplying them by 100, keeping a reasonable precision
                    // while saving space on the hardware that would otherwise be lost if 
                    // floats were used.
                    tempseries.getData().add(new XYChart.Data<>(time, vals[0]/100));
                    humidityseries.getData().add(new XYChart.Data<>(time, vals[1]/100)); 
                    motionseriesX.getData().add(new XYChart.Data<>(time, vals[2]));
                    motionseriesY.getData().add(new XYChart.Data<>(time, vals[3]));
                    motionseriesZ.getData().add(new XYChart.Data<>(time, vals[4])); 
                }
                catch(NumberFormatException ex){} // throw out records in bad format
            }

            // set series legend names //
            motionseriesX.setName(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("X-AXIS"));
            motionseriesY.setName(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("Y-AXIS"));
            motionseriesZ.setName(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("Z-AXIS"));
            tempseries.setName(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("TEMPERATURE_nocel"));
            humidityseries.setName(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("HUMIDITYLEVEL"));
            
            // set data with series //
            MOTION.getData().add(motionseriesX);
            MOTION.getData().add(motionseriesY);
            MOTION.getData().add(motionseriesZ);
            TEMP.getData().add(tempseries);
            HUMIDITY.getData().add(humidityseries);


            // Set boundaries for red y-axis //
            TempyAxis.setLowerBound(minVal-2);
            TempyAxis.setUpperBound(maxVal+2);

        }
       
    }
    
    /* *************************************************************************
    * Resets and clears filters for the data list, showing all measurements from
    * any terminal, sensor, and date, and updates the sand temperature labels,
    * which are described further in the function overview comment for the function
    * "updateSandTempLabel()".
    ***************************************************************************/
    @FXML
    private void resetButtonAction(ActionEvent event) {
        System.out.println("Filters Reset.");
        try {
            updateSandTempLabel();
        } catch (FileNotFoundException ex) {

        }
        datePickFilter.getEditor().clear(); // clear the date field
        datePickFilter.setValue(null); 
        
        terminalSelector.setValue(null);
        sensorSelector.setValue(null);
        terminalSelector.getEditor().clear();
        sensorSelector.getEditor().clear();
        sensorSelector.disableProperty().set(true);
        
        populateDataField(null,-1,-1); // show all with no filters
        
    }
    
    /* *************************************************************************
    * Function that updates the text of the service toggle button to represent the
    * current state of the service. Should be called in a timer.
    ***************************************************************************/
    @FXML
    private void updateServiceStatus(){
        int status = MUTSLibrary.getServiceState("MUTSService");
        if(status == 1){
            serviceControlButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MONITORINGISON"));
        }
        else
        {
            serviceControlButton.setText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("MONITORINGISOFF."));
        }
    
    }
    
    /* *************************************************************************
    * Function to be called periodically that will check for new sand temperature
    * data files (those with S_ preceeding the standard file name). The function 
    * updates the label controls for the three depths of temperature the system
    * measures: Shallow, Mid, and Deep. It does this by looking at all files, for
    * each cluster in the S-Web, then determines which temperature probe measured
    * the highest temperature most recently and does this for each of the three
    * depths. This is done to provide a general overview of maximum recorded temperature
    * for any given probe in the web, since it is all we are concerned about. More
    * detail on sand temperature is found by clicking the "Sand History" button.
    ***************************************************************************/
    private void updateSandTempLabel() throws FileNotFoundException
    {
        LocalDate date = LocalDate.now();
        String filename;
        double[] tempArray = new double[3]; // 0 = shallow, 1 = mid, 2 = deep
        double readtemp;
        for(double temp : tempArray){
            temp = -100.0;
        }
        File[] files = new File(DataDirectory).listFiles();
        if (files != null) 
        {
            for (File file : files) {
                if (file.isFile()) {
                    filename = file.getName();
                    if (filename.endsWith(".csv") && 
                        filename.startsWith(String.format("S_%s%s%s_", String.format("%02d",date.getMonthValue()),
                                String.format("%02d",date.getDayOfMonth()),date.getYear()))
                    ){ 
                        try (Scanner sc = new Scanner(file)) {
                            sc.useDelimiter(",|\\n");
                            sc.next(); sc.next(); sc.next(); sc.next(); // toss time,country code, arduino number, and cluster number.
                            for(int i = 0; i < 3; i++){
                                readtemp = Double.parseDouble(sc.next())/100.0;
                                if (tempArray[i] < readtemp)
                                    tempArray[i] = readtemp;
                            }
                        }
                    }
                }
            }
            TEMPShallowlabel.setText(String.valueOf(tempArray[0]));
            TEMPMidlabel.setText(String.valueOf(tempArray[1]));
            TEMPDeeplabel.setText(String.valueOf(tempArray[2]));
        } 
        else 
        {
            TEMPShallowlabel.setText("N/A");
            TEMPMidlabel.setText("N/A");
            TEMPDeeplabel.setText("N/A");
        }

    }
    

    /* *************************************************************************
    * Function handles a user interaction with the button labeled "Sand History"
    * The function opens the SandTemp.fxml file and generates a stage from it,
    * setting its controller to the SandTempController.java class. This new window
    * contains data regarding the temperature recorded by the S-Web temperature probes
    ***************************************************************************/
    @FXML
    public void handleSandHistoryBtn(ActionEvent event) {
        Parent sandscene;
        try {

            sandscene = FXMLLoader.load(getClass().getResource("SandTemp.fxml"));
            Stage stage = new Stage();
            stage.setTitle(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("SAND TEMPERATURE HISTORIC DATA"));
            stage.setScene(new Scene(sandscene,800,450));
            stage.show();

        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    /* *************************************************************************
    * Function handles a user interaction with the Settings MenuBar item labeled
    * "Change/Set Data Transfer Location". Will open a new window allowing the user
    * to set the location of data which is incoming from the transfer radio.
    ***************************************************************************/
    @FXML
    public void handleSetDataDestMenu(ActionEvent event) {
        DataDestForm awindow = new DataDestForm(pref);
        awindow.setDefaultCloseOperation(1);
        awindow.setLocationRelativeTo(null);
        awindow.setDefaultCloseOperation(awindow.DISPOSE_ON_CLOSE);
        awindow.setVisible(true);
        awindow.setAlwaysOnTop(true);
        awindow.requestFocus();

    }

    /* *************************************************************************
    * This function performs a check in the data folder for new data and fills the
    * data field control with the appropriate list items associated with the data
    * files that only match with the given filters date, terminalID, and sensorID.
    ***************************************************************************/
    private void populateDataField(LocalDate date, int terminalID, int sensorID) {
        // files should be named: MMDDYYYY_XXXYYYZZ.csv
        dataList.getItems().clear(); // remove all current list items
        results.clear();
        List<String> removedresults = new ArrayList<>();
        String filename;
        String tempField;
        File[] files = new File(DataDirectory).listFiles();
        sensorSelector.disableProperty().set(true);
        if (files != null) {
            sensorSelector.disableProperty().set(false);
            for (File file : files) {
                if (file.isFile()) {
                    filename = file.getName();
                    if (filename.endsWith(".csv") && filename.length() == 21){ 
                        results.add(filename.substring(0, filename.length() - 4));
                    }
                }
            }
            
            if(date != null) { // if filter by date
                for (String logitem : results) {
                    if (Integer.parseInt(logitem.substring(0, 2)) != date.getMonthValue() ||
                        Integer.parseInt(logitem.substring(2, 4)) != date.getDayOfMonth() ||
                        Integer.parseInt(logitem.substring(4, 8)) != date.getYear() ) {
                            removedresults.add(logitem);     
                    }
                }
            }
            
            if(terminalID >= 0) { // if filter by terminal
                for (String logitem : results) {
                    if (Integer.parseInt(logitem.substring(12, 15)) != terminalID)
                        removedresults.add(logitem);  
                }
            }
            
            if(sensorID >= 0) { // if filter by sensor
                for (String logitem : results) {
                    if (Integer.parseInt(logitem.substring(15, 17)) != sensorID)
                        removedresults.add(logitem);   
                }
            }
            
            
            results.removeAll(removedresults);
            removedresults.clear();
            
            // removedresults are those files that are in the Data directory, but not desired.
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
                String terminal = String.valueOf(Integer.parseInt(result.substring(12,15)));
                String sensor = String.valueOf(Integer.parseInt(result.substring(15,17)));
                tempField = result.substring(0,2) + '/' + result.substring(2,4) + '/' +  result.substring(4,8);
                tempField += "--Ter " + terminal;
                tempField += "--Sen " + sensor;
                removedresults.add(tempField);
                if(!terminalSelector.getItems().contains(terminal))
                    terminalSelector.getItems().add(terminal);
                if(!sensorSelector.getItems().contains(sensor))
                    sensorSelector.getItems().add(sensor);
            } 
            dataList.getItems().addAll(removedresults);
        }
        
    }
    
             
    @FXML
    private void showAbout(){
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("ABOUT"));
        alert.setHeaderText(null);
        alert.setContentText(java.util.ResourceBundle.getBundle("muts_java/ES_Bundle_es_GT").getString("ABOUTMessage"));

        alert.showAndWait();

    }
}
