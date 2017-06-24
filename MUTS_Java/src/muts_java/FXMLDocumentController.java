/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.print.PageLayout;
import javafx.print.PageOrientation;
import javafx.print.Paper;
import javafx.print.Printer;
import javafx.print.PrinterAttributes;
import javafx.print.PrinterJob;
import javafx.scene.Node;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.ComboBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TabPane;
import javafx.scene.transform.Scale;


/**
 *
 * @author derek
 */
public class FXMLDocumentController implements Initializable {
    private final String DataDirectory;
    private final List<String> results = new ArrayList<>();
    
    
    @FXML
    private Label label;
    
    @FXML
    private DatePicker datePickFilter;
    @FXML
    private ComboBox terminalSelector, sensorSelector;
    @FXML
    private ListView dataList;
    @FXML
    private LineChart<String,Number> BLUETEMP;
    @FXML
    private LineChart<String,Number> YELLOWTEMP;
    @FXML
    private LineChart<String,Number> REDTEMP;
    @FXML
    private LineChart<String,Number> MOTION;
    @FXML
    private NumberAxis MotionyAxis;
    @FXML
    private CategoryAxis MotionxAxis;
    @FXML
    private NumberAxis RedyAxis;
    @FXML
    private CategoryAxis RedxAxis;
    @FXML
    private NumberAxis YellowyAxis;
    @FXML
    private CategoryAxis YellowxAxis;
    @FXML
    private NumberAxis BlueyAxis;
    @FXML
    private CategoryAxis BluexAxis;
    @FXML
    private TabPane graphTabs;
    
    public FXMLDocumentController() {
        this.DataDirectory = "E:/testprograms/MUTS_Java/DATA";

        
    }
    
    @FXML
    private void handleButtonAction(ActionEvent event) {
        System.out.println("You clicked me!");
        label.setText("Hello World!");
    }
    
    @FXML
    private void handlePrintGraph(ActionEvent event) {
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
        Scale scale = new Scale(scaleX, scaleY);
       // toPrint.getTransforms().add(scale); 


        if (pj != null) {
            boolean success = pj.printPage(toPrint);
                if (success) {
                    pj.endJob();
                } 
        }  
 //       toPrint.getTransforms().remove(scale); */
    }
    
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
    
    @FXML
    private void handleDataFileChosen(Event event) throws FileNotFoundException {
        // Remove preexisting graphed data, if any //
        MOTION.getData().clear();
        REDTEMP.getData().clear();
        BLUETEMP.getData().clear();
        YELLOWTEMP.getData().clear();

        String filename = DataDirectory + '/' + results.get(dataList.getSelectionModel().getSelectedIndex());
        double[] vals = new double[6]; // array for storing values for each graph. The six
                                    // elements represent, in an order determined by while loop below,
                                    // red, blue, and green temperatures, and x,y, and z motion data.
        double[] minVal = new double[3]; // The minimum values for each of the three temp measurements
        double[] maxVal = new double[3]; // the max values for each of the three temp measurements.
        // initialize min and max value arrays. These values are later used for setting the y-axis range.
        for (int i = 0; i < 3; i++){
            minVal[i] = Double.MAX_VALUE;
            maxVal[i] = Double.MIN_VALUE;
        }

        File inputfile = new File(filename + ".txt"); 
        Scanner sc = new Scanner(inputfile);
        sc.useDelimiter(",|\\n");
        
        
        sc.nextLine(); // toss header
        String time = sc.next(); // the first data point should be the time.
        String countryCode = sc.next();
        String terminalNum = sc.next();
        String sensorNum = sc.next();
        
        // set titles for charts //
        MOTION.titleProperty().set("Motion Data For Terminal " + terminalNum + " - Sensor " + sensorNum);
        REDTEMP.titleProperty().set("Red Temperature Data For Terminal " + terminalNum + " - Sensor " + sensorNum);
        BLUETEMP.titleProperty().set("Blue Temperature Data For Terminal " + terminalNum + " - Sensor " + sensorNum);
        YELLOWTEMP.titleProperty().set("Yellow Temperature Data For Terminal " + terminalNum + " - Sensor " + sensorNum);
        
        // The series are initialized and data is added to them. At the end of this call, they are
        // used to populate the graphs with data.
        XYChart.Series motionseriesX = new XYChart.Series<>();
        XYChart.Series motionseriesY = new XYChart.Series<>();
        XYChart.Series motionseriesZ = new XYChart.Series<>();
        XYChart.Series redseries = new XYChart.Series<>();
        XYChart.Series yellowseries = new XYChart.Series<>();
        XYChart.Series blueseries = new XYChart.Series<>();
        
        // read data from file //
        while(sc.hasNext()){
            
            for(int i = 0; i < 6 && sc.hasNext(); i++){ // checking hasNext twice to ensure there is still data to read.
                vals[i] = Double.parseDouble(sc.next());
                
                if(i <=2 && vals[i]/100.0 < minVal[i]){ // setting min and max values.
                    minVal[i] = vals[i]/100.0; // set new min
                } else if(i <=2 && vals[i]/100.0 >= maxVal[i]){
                    maxVal[i] = vals[i]/100.0; // set new max
                }
                
            }
            
            // temps are divided by 100 because sensors record floating point values
            // into short values by multiplying them by 100, keeping a reasonable precision
            // while saving space on the hardware that would otherwise be lost if 
            // floats were used.
            blueseries.getData().add(new XYChart.Data<>(time, vals[0]/100.0));
            yellowseries.getData().add(new XYChart.Data<>(time, vals[1]/100.0));
            redseries.getData().add(new XYChart.Data<>(time, vals[2]/100.0));
            motionseriesX.getData().add(new XYChart.Data<>(time, vals[3]));
            motionseriesY.getData().add(new XYChart.Data<>(time, vals[4]));
            motionseriesZ.getData().add(new XYChart.Data<>(time, vals[5])); 

            sc.next(); // drop date
            if(sc.hasNext()) { // if there is another line after the \n, keep reading
                time = sc.next();
                sc.next(); sc.next(); sc.next(); // toss codes
            }
        }

        sc.close(); // close scanner out
        
        // set series legend names //
        motionseriesX.setName("x-axis");
        motionseriesY.setName("y-axis");
        motionseriesZ.setName("z-axis");
        
        // set data with series //
        MOTION.getData().add(motionseriesX);
        MOTION.getData().add(motionseriesY);
        MOTION.getData().add(motionseriesZ);
        REDTEMP.getData().add(redseries);
        BLUETEMP.getData().add(blueseries);
        YELLOWTEMP.getData().add(yellowseries);
        
        // Remove dotted nodes //
        MOTION.setCreateSymbols(false);
        REDTEMP.setCreateSymbols(false);
        BLUETEMP.setCreateSymbols(false);
        YELLOWTEMP.setCreateSymbols(false);  
        
        // Set boundaries for red y-axis //
        RedyAxis.setLowerBound(minVal[2]-2);
        RedyAxis.setUpperBound(maxVal[2]+2);
        // Set boundaries for yellow y-axis //
        YellowyAxis.setLowerBound(minVal[1]-2);
        YellowyAxis.setUpperBound(maxVal[1]+2);
        // Set boundaries for blue y-axis //
        BlueyAxis.setLowerBound(minVal[0]-2);
        BlueyAxis.setUpperBound(maxVal[0]+2);
        
       
    }
    
    
    @FXML
    private void resetButtonAction(ActionEvent event) {
        System.out.println("Filters Reset.");
        
        datePickFilter.getEditor().clear(); // clear the date field
        datePickFilter.setValue(null); 
        
        terminalSelector.setValue(null);
        sensorSelector.setValue(null);
        terminalSelector.getEditor().clear();
        sensorSelector.getEditor().clear();
        sensorSelector.disableProperty().set(true);
        
        populateDataField(null,-1,-1); // show all with no filters
        
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
        populateDataField(null,-1,-1);
        
        // set motion y axis range properties
        MotionyAxis.setAutoRanging(false);
        MotionyAxis.setLowerBound(450);
        MotionyAxis.setTickUnit(10);
        MotionyAxis.setUpperBound(550);
        MotionyAxis.setLabel("Movement Intensity");
        // set motion x axis properties
        MotionxAxis.setAutoRanging(true);
        MotionxAxis.setTickLabelFont(new javafx.scene.text.Font("System",18));
        MotionxAxis.setLabel("Time");
        // set red x axis properties
        RedxAxis.setAutoRanging(true);
        RedxAxis.setTickLabelFont(new javafx.scene.text.Font("System",18));
        RedxAxis.setLabel("Time");
        // set red y axis range properties
        RedyAxis.setTickLabelFont(new javafx.scene.text.Font("System",14));
        RedyAxis.setAutoRanging(false);
        RedyAxis.setLowerBound(0);
        RedyAxis.setTickUnit(1);
        RedyAxis.setUpperBound(45);
        RedyAxis.setLabel("Temperature (degrees Celcius)");
        
        // set yellow x axis properties
        YellowxAxis.setAutoRanging(true);
        YellowxAxis.setTickLabelFont(new javafx.scene.text.Font("System",18));
        YellowxAxis.setLabel("Time");
        // set yellow y axis range properties
        YellowyAxis.setTickLabelFont(new javafx.scene.text.Font("System",14));
        YellowyAxis.setAutoRanging(false);
        YellowyAxis.setLowerBound(0);
        YellowyAxis.setTickUnit(1);
        YellowyAxis.setUpperBound(45);
        YellowyAxis.setLabel("Temperature (degrees Celcius)");
        // set blue x axis properties
        BluexAxis.setAutoRanging(true);
        BluexAxis.setTickLabelFont(new javafx.scene.text.Font("System",18));
        BluexAxis.setLabel("Time");
        // set blue y axis range properties
        BlueyAxis.setTickLabelFont(new javafx.scene.text.Font("System",14));
        BlueyAxis.setAutoRanging(false);
        BlueyAxis.setLowerBound(0);
        BlueyAxis.setTickUnit(1);
        BlueyAxis.setUpperBound(45);
        BlueyAxis.setLabel("Temperature (degrees Celcius)");

    }
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
                    if (filename.endsWith(".txt") && filename.length() == 21){
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
    
}
