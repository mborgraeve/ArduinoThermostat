  /*
 * Oscilloscope
 * Gives a visual rendering of analog pin 0 in realtime.
 * 
 * This project is part of Accrochages
 * See http://accrochages.drone.ws
 * 
 * (c) 2008 Sofian Audry (info@sofianaudry.com)
 *
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
import processing.serial.*;

Serial port;  // Create object from Serial class
int val;      // Data received from the serial port
int[] drv;
int[] v;
float zoom;

int getY(int val) {
  return (int)(height - val / 1023.0f * (height - 1));
}

void setup() 
{
  size(1280, 1000);
  // Open the port that the board is connected to and use the same speed (9600 bps)
  port = new Serial(this, Serial.list()[0], 115200);
  v = new int[width];
  drv = new int[width];
  zoom = 1.0f;
  smooth();
}

void pushValues(int drv1, int v1) {
  for (int i=0; i<width-1; i++){
    v[i] = v[i+1];
    drv[i] = drv[i+1];
  }
  drv[width-1] = drv1;
  v[width-1] = v1;
}

void drawLines() {
  
  stroke(255,0,0);
  textSize(32);
  
  text(str(v[v.length-1]),50,50);
  int displayWidth = (int) (width / zoom);
  
  int k = v.length - displayWidth;
  
  //int x0 = 0;
  //int y0 = getY(v[k]);
  for (int i=1; i<displayWidth; i++) {
    k++;
    int x1 = (int) (i * (width-1) / (displayWidth-1));
    int y1 = getY(v[k]);
    //line(x0, y0, x1, y1);
    point(x1,y1);
    //x0 = x1;
    //y0 = y1;
  }
  stroke(0,255,0);
  textSize(32);
  
  text(str(drv[drv.length-1]),50,100);
  displayWidth = (int) (width / zoom);
  
  k = drv.length - displayWidth;
  
  //x0 = 0;
  //y0 = getY(drv[k]);
  for (int i=1; i<displayWidth; i++) {
    k++;
    int x1 = (int) (i * (width-1) / (displayWidth-1));
    int y1 = getY(drv[k]);
    //line(x0, y0, x1, y1);
    point(x1,y1);
    //x0 = x1;
    //y0 = y1;
  }
}

void drawGrid() {
  stroke(255, 0, 0);
  line(0, height/2, width, height/2);
}

void keyReleased() {
  switch (key) {
    case '+':
      zoom *= 2.0f;
      println(zoom);
      if ( (int) (width / zoom) <= 1 )
        zoom /= 2.0f;
      break;
    case '-':
      zoom /= 2.0f;
      if (zoom < 1.0f)
        zoom *= 2.0f;
      break;
  }
}

void draw()
{
  background(0);
  drawGrid();
  int drv = -1;
  int v = -1;
  {
 while (port.available() >= 5) {
    if (port.read() == 0xff) {
      drv = (port.read() << 8) | (port.read());
      
      v = (port.read() << 8) | (port.read());
    }
  }}
  //if (v != -1 || drv != -1)
  {
    pushValues(v,drv);
  }
  drawLines();
}