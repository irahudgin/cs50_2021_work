#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    int ravg; // rounded pixel value average
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0) + 0.5;
            ravg = avg; // rounded pixel value average
            image[i][j].rgbtBlue = ravg;
            image[i][j].rgbtGreen = ravg;
            image[i][j].rgbtRed = ravg;
            
        }
    }
    
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int blue;
    int green;
    int red;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = ((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189)) + 0.5;
            green = ((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168)) + 0.5;
            blue = ((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131)) + 0.5;
            
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtRed = red;
            
        }
    }
    
    return;
}

// reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width]; // loop variable buffer to store image
    
    for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                buffer[i][j].rgbtBlue = image[i][j].rgbtBlue;
                buffer[i][j].rgbtGreen = image[i][j].rgbtGreen;
                buffer[i][j].rgbtRed = image[i][j].rgbtRed;
                
            }
        }

    // Writing image from buffer, backwards per row
    for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[i][j].rgbtBlue = buffer[i][(width - 1) - j].rgbtBlue;
                image[i][j].rgbtGreen = buffer[i][(width - 1) - j].rgbtGreen;
                image[i][j].rgbtRed = buffer[i][(width - 1) - j].rgbtRed;
                
            }
        }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    RGBTRIPLE tl;
    RGBTRIPLE to;
    RGBTRIPLE tr;
    RGBTRIPLE mr;
    RGBTRIPLE mm;
    RGBTRIPLE ml;
    RGBTRIPLE bl;
    RGBTRIPLE bo;
    RGBTRIPLE br;
    
    for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                buffer[i][j].rgbtBlue = image[i][j].rgbtBlue;
                buffer[i][j].rgbtGreen = image[i][j].rgbtGreen;
                buffer[i][j].rgbtRed = image[i][j].rgbtRed;
                
            }
        }
    
    
    float blueavg;
    float redavg;
    float greenavg;
    int ravg;
    int bavg;
    int gavg;
    
    for (int i = 0; i < height; i++) // this is every row of pixels
    {
        
        for (int j = 0; j < width; j++) // this loop is for each pixel of i height and j width
        {
            blueavg = 0;
            redavg = 0;
            greenavg = 0;
            ravg = 0;
            bavg = 0;
            gavg = 0;
            
            if (i == 0 && j == 0) // top left corner
            {
                mm = buffer[i][j];
                bo = buffer[i + 1][j];
                br = buffer[i + 1][j + 1];
                mr = buffer[i][j + 1]; 
                
                blueavg = (mm.rgbtBlue + bo.rgbtBlue + br.rgbtBlue + mr.rgbtBlue) / 4.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + bo.rgbtGreen + br.rgbtGreen + mr.rgbtGreen) / 4.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + bo.rgbtRed + br.rgbtRed + mr.rgbtRed) / 4.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
                continue;
            }
            
            if (i == 0 && j == (width - 1)) // top right corner
            {
                mm = buffer[i][j];
                ml = buffer[i][j - 1];
                bl = buffer[i + 1][j - 1];
                bo = buffer[i + 1][j];
               
                blueavg = (mm.rgbtBlue + bo.rgbtBlue + ml.rgbtBlue + bl.rgbtBlue) / 4.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + bo.rgbtGreen + ml.rgbtGreen + bl.rgbtGreen) / 4.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + bo.rgbtRed + ml.rgbtRed + bl.rgbtRed) / 4.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
                continue;
                
            }
            
            if (i == (height - 1) && j == 0) // bottom left corner
            {
            
                to = buffer[i - 1][j];
                tr = buffer[i - 1][j + 1];
                mr = buffer[i][j + 1];             
                mm = buffer[i][j];
                
                blueavg = (mm.rgbtBlue + bo.rgbtBlue + br.rgbtBlue + mr.rgbtBlue) / 4.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + bo.rgbtGreen + br.rgbtGreen + mr.rgbtGreen) / 4.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + bo.rgbtRed + br.rgbtRed + mr.rgbtRed) / 4.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
                continue;
            
            }
            
            if (i == (height - 1) && j == (width - 1)) // bottom right corner
            {
                mm = buffer[i][j];
                ml = buffer[i][j - 1];
                bl = buffer[i + 1][j - 1];
                bo = buffer[i + 1][j];
                
                blueavg = (mm.rgbtBlue + bo.rgbtBlue + bl.rgbtBlue + ml.rgbtBlue) / 4.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + bo.rgbtGreen + bl.rgbtGreen + ml.rgbtGreen) / 4.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + bo.rgbtRed + bl.rgbtRed + ml.rgbtRed) / 4.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
                continue;
                
            }
            
            if (i == 0) // top pixels
            {
                mr = buffer[i][j + 1];             
                mm = buffer[i][j];
                ml = buffer[i][j - 1];
                bl = buffer[i + 1][j - 1];
                bo = buffer[i + 1][j];
                br = buffer[i + 1][j + 1];
                
                blueavg = (mm.rgbtBlue + bo.rgbtBlue + br.rgbtBlue + mr.rgbtBlue + ml.rgbtBlue + bl.rgbtBlue) / 6.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + bo.rgbtGreen + br.rgbtGreen + mr.rgbtGreen + ml.rgbtGreen + bl.rgbtGreen) / 6.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + bo.rgbtRed + br.rgbtRed + mr.rgbtRed + ml.rgbtRed + bl.rgbtRed) / 6.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
                continue;
            }
            
            if (i == (height - 1)) // bottom pixels
            {
                tl = buffer[i - 1][j - 1];
                to = buffer[i - 1][j];
                tr = buffer[i - 1][j + 1];
                mr = buffer[i][j + 1];             
                mm = buffer[i][j];
                ml = buffer[i][j - 1];
                
                blueavg = (mm.rgbtBlue + to.rgbtBlue + tr.rgbtBlue + mr.rgbtBlue + ml.rgbtBlue + tl.rgbtBlue) / 6.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + to.rgbtGreen + tr.rgbtGreen + mr.rgbtGreen + ml.rgbtGreen + tl.rgbtGreen) / 6.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + to.rgbtRed + tr.rgbtRed + mr.rgbtRed + ml.rgbtRed + tl.rgbtRed) / 6.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
                continue;
            
            }
            
            if (j == 0) // left side
            {
                to = buffer[i - 1][j];
                tr = buffer[i - 1][j + 1];
                mr = buffer[i][j + 1];             
                mm = buffer[i][j];
                bo = buffer[i + 1][j];
                br = buffer[i + 1][j + 1];
                
                blueavg = (mm.rgbtBlue + bo.rgbtBlue + br.rgbtBlue + mr.rgbtBlue + tr.rgbtBlue + to.rgbtBlue) / 6.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + bo.rgbtGreen + br.rgbtGreen + mr.rgbtGreen + tr.rgbtGreen + to.rgbtGreen) / 6.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + bo.rgbtRed + br.rgbtRed + mr.rgbtRed + tr.rgbtRed + to.rgbtRed) / 6.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
                continue;
                
            }
            
            if (j == (width - 1)) // right side
            {
            
                mm = buffer[i][j];
                ml = buffer[i][j - 1];
                bl = buffer[i + 1][j - 1];
                bo = buffer[i + 1][j];
                tl = buffer[i - 1][j - 1];
                to = buffer[i - 1][j];
                
                blueavg = (mm.rgbtBlue + bo.rgbtBlue + bl.rgbtBlue + ml.rgbtBlue + tl.rgbtBlue + to.rgbtBlue) / 6.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + bo.rgbtGreen + bl.rgbtGreen + ml.rgbtGreen + tl.rgbtGreen + to.rgbtGreen) / 6.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + bo.rgbtRed + bl.rgbtRed + ml.rgbtRed + tl.rgbtRed + to.rgbtRed) / 6.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
                continue;
                
            }
            
                tl = buffer[i - 1][j - 1];
                to = buffer[i - 1][j];
                tr = buffer[i - 1][j + 1];
                mr = buffer[i][j + 1];             
                mm = buffer[i][j];
                ml = buffer[i][j - 1];
                bl = buffer[i + 1][j - 1];
                bo = buffer[i + 1][j];
                br = buffer[i + 1][j + 1];
                
                blueavg = (mm.rgbtBlue + bo.rgbtBlue + br.rgbtBlue + mr.rgbtBlue + tr.rgbtBlue + to.rgbtBlue + ml.rgbtBlue + bl.rgbtBlue + tl.rgbtBlue) / 9.0;
                bavg = blueavg + 0.5;
                
                greenavg = (mm.rgbtGreen + bo.rgbtGreen + br.rgbtGreen + mr.rgbtGreen + tr.rgbtGreen + to.rgbtGreen + ml.rgbtGreen + bl.rgbtGreen + tl.rgbtGreen) / 9.0;
                gavg = greenavg + 0.5;
                
                redavg = (mm.rgbtRed + bo.rgbtRed + br.rgbtRed + mr.rgbtRed + tr.rgbtRed + to.rgbtRed + ml.rgbtRed + bl.rgbtRed + tl.rgbtRed) / 9.0;
                ravg = redavg + 0.5;
                
                image[i][j].rgbtBlue = bavg;
                image[i][j].rgbtGreen = gavg;
                image[i][j].rgbtRed = ravg;
            
        }
    }
    
    return;
}
