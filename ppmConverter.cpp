#include "ppmConverter.h"


PPM ::~PPM() {} //Destructor

void PPM ::convertAndOutput()
{
    if (readppm() == -1)    //reading the ppm file fails
    {
        return;
    }
    writetopgm();   //write the ppm file data in pgm format
}

int PPM ::readppm()
{
    RGB temp;
    int index = 0;  //to know which color should the value be written to

    string s;   //to store input

    //flags to indicate completeness of header 
    bool got_mgnum = false, got_width = false, got_height = false, got_maxcolorval = false;

    
    vector<string> tokens;
    pixels.clear();

    ifstream ifp = loadFile();
    
        
    //get each line from the input file at a time
    while (getline(ifp, s))
    {
        try
        {
            //Each line has to be of less than 70 characters
            if (s.size() > 70)
            {
                throw "More than 70 characters in a line";
            }

            tokens.clear();
            tokens = split(s, ' '); //split around blanks to get non-blank characters
            
            for (string t : tokens)
            {
                if (!t.empty() && t[0] != ' ' && t[0] != '\t' && t[0] != '\v' && t[0] != '\f') //ignoring tokens with whitespace
                {
                    if (t[0] == '#')    //stop parsing the line when a comment is detected
                    {
                        break;
                    }
                    else
                    {
                        if (got_mgnum == false) //magic number not found 
                        {
                            if (t.compare("P3") == 0) //t=P3
                            {
                                got_mgnum = true;
                                break;
                            }
                            else
                            {
                                throw "Invalid file format-not a ppm file";
                            }
                        }
                        else if (got_width == false)    //width not found
                        {
                            width = stoi(t);
                            if (width <= 0)
                            {
                                throw "Invalid width";
                            }
                            got_width = true;
                        }
                        else if (got_height == false)   //height not found
                        {
                            height = stoi(t);
                            if (height <= 0)
                            {
                                throw "Invalid height";
                            }
                            got_height = true;
                            break;
                        }
                        else if (got_maxcolorval == false)  //max color value not found
                        {
                            maxcolorval = stoi(t);
                            if (!(maxcolorval > 0 && maxcolorval < 65536))
                            {
                                throw "Invalid maximum color value";
                            }
                            got_maxcolorval = true;
                            break;
                        }
                        else //pixel data input
                        {
                            int val = stoi(t);
                            if (!(val >= 0 && val <= maxcolorval))
                            {
                                throw "Color value not in given range";
                            }
                            else
                            {
                                if (index == 0) //red value input
                                {
                                    temp.red = val;
                                    index++;
                                }
                                else if (index == 1)    //green value input
                                {
                                    temp.green = val;
                                    index++;
                                }
                                else if (index == 2)    //blue value input
                                {
                                    temp.blue = val;
                                    index = 0;
                                    pixels.push_back(temp);
                                }
                            }
                        }
                    }
                }
            }
            if (got_width == true && got_height == false)
            {
                throw "Width and height not in same line";
            }
        }
        catch (const char *e)
        {
            cout << '\n' << e << "\n\n";
            ifp.close();    //close the input file
            return -1;
        }
    }
    ifp.close();
    
    try
    {
        if (!got_mgnum || !got_width || !got_height || !got_maxcolorval)
        {
            throw "Header incomplete";
        }
        if (pixels.size() != (width * height))
        {
            throw "Insufficient pixel data provided";
        }
    }
    catch (const char *e)
    {
        cout << '\n' << e << "\n\n";
        return -1;
    }
    return 0;
}

void PPM ::writetopgm()
{ 
    //create the output file as currentfilename(without extension).pgm
    vector<string> tokens = split(currentFile,'.');
    string outputfileName = "";
    
    for(string s: tokens)
    {
        if(s!=tokens.back())
        {
            outputfileName  = outputfileName + s + '.';
        }
    }
    outputfileName += "pgm";

    ofstream ofp(outputfileName.c_str());   //open output file for writing
    try
    {
        if (ofp.fail())
        {
            throw "Output file not created";
        }
        
        //writing the header of PGM file
        ofp << "P2\n"
            << to_string(width) << " " << to_string(height) << '\n'
            << to_string(maxcolorval) << '\n';
        
        //writing the pixel data in PGM value
        int count = 0;
        for (RGB p : pixels)
        {
            ofp << to_string(rgbTograyscale(p)) << " "; //convert RGB of pixel in PPM to grayscale value
            count++;
            if (count == width)
            {
                ofp << '\n';
                count = 0;
            }
        }
    }
    catch (const char *e)
    {
        cout << e << '\n';
    }
    
    ofp.close();
    cout << '\n' << outputfileName << " file has been created Successfully :)" << "\n\n";
}

int PPM :: rgbTograyscale(RGB p)
{
    return (0.3 * p.red) + (0.59 * p.green) + (0.11 * p.blue);
}
