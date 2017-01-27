// Settings data class
public class Settings
{
    // orgDataPath: The file path used by R to aquire the organized data file.
    public string DataPath = "T:/Documents/TurtleProject/Turtle_Project/TurtleDesktopClient/DATA";
    // rBinPath: The location of the r binary file. Must point to the 32-bit edition
    public string rBinPath = @"F:\Programs\R\R-3.3.2\bin\i386";
    public string countryCode = "108"; // the first three digits of a board. Same for all data since our program is ran in the set country.
    public int maxTerminals = 200; // the most terminals allowed on the program.
    public int maxSensors = 3; // the most sensors allowed per terminal.
    public int maxCollections = 99; // most collections in a day.
    public Settings()
	{
	}
}
