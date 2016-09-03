int stripLengthFront[24] = {3, 3, 7, 4, 8, 5, 10, 10, 10, 10, 8, 9, 8, 8, 9, 9, 10, 10, 7, 9, 6, 8, 3, 6};  //180 pixels
int stripLengthBack1[10] = {4,7,10,10,11,10,10,10,10,10};       //92 pixels
int stripLengthBack2[10] = {5,7,10,10,11,10,10,10,10,10};       //93 pixels


int taylorTopLongY[] = { 

      1,
      3,
      5,
      7,
      9,
      11,
      13,
      15,
      17,
      19,

      19,
      17,
      15,
      13,
      11,
      9,
      7,
      5,
      3,
      1,

      2,
      4,
      6,
      8,
      10,
      12,
      14,
      16,
      18,
      20,

      19,
      17,
      15,
      13,
      11,
      9,
      7,
      5,
      3,
      1,

      2,
      4,
      6,
      8,
      10,
      12,
      14,
      16,
      18,
      20,

      21,
      19,
      17,
      15,
      13,
      11,
      9,
      7,
      5,
      3,
      1,

      2,
      4,
      6,
      8,
      10,
      12,
      14,
      16,
      18,
      20,

      19,
      17,
      15,
      13,
      11,
      9,
      7,
      5,
      3,
      1,

      2,
      4,
      6,
      8,
      10,
      16,
      18,

      17,
      8,
      6,
      4,








      2,
      4,
      6,
      8,

      7,
      5,
      3,

      2,
      4,
      6,
      8,
      19,

      20,
      18,
      8,
      6,
      4,
      3,

      4,
      6,
      8,
      10,
      12,
      15,
      17,
      19,

      18,
      16,
      14,
      12,
      10,
      8,
      6,

      7,
      9,
      11,
      13,
      15,
      17,
      20,

      // 21,
      19,
      17,
      15,
      13,
      11,
      9,
      7,
      5,
      2,

      1,
      3,
      5,
      7,
      9,
      11,  //9
      13,
      15,
      17,
      // 19,

      // 18,
      16,
      14,
      12,
      10,     //10
      8,
      6,
      4,
      2,

      1,
      3,
      5,
      7,          //11
      9,
      11,
      13,
      15,
      // 17,

      16,
      14,
      12,
      10,
      8,            //12
      6,
      4,
      2,

      1,
      3,
      5,
      7,
      9,              //13
      11,
      13,
      15,
      // 17,

      // 17,
      15,
      13,
      11,             //14
      9,
      7,
      5,
      3,

      2,
      4,
      6,
      8,
      10,               //15
      12,
      14,
      16,
      // 18,

      // 19,
      17,
      15,
      13,
      11,                     //16
      9,
      7,
      5,
      2,

      1,
      3,
      5,
      7,                  //17
      9,
      11,
      13,
      15,
      17,
      // 19,

      // 20,
      18,
      16,
      14,             //18
      12,
      10,
      8,
      6,
      4,
      2,

      7,
      9,
      11,
      13,             //19
      15,
      17,
      19,

      20,
      18,
      16,                   //20
      14,
      12,
      10,
      8,
      6,

      5,
      7,
      9,
      11,
      13,
      15,
      17,
      19,

      9,
      7,
      5,
      3,

      2,
      4,
      6,
      8,
      18,
      20,

      19,
      8,
      6,
      4,

      2,
      4,
      6,





        3,
        5,
        7,
        9,
        18,
        19,
        17,
        11,
        9,
        7,
        5,
        3,
        2,
        4,
        6,
        8,
        10,
        12,
        14,
        16,
        18,
        20,
        21,
        19,
        17,
        15,
        13,
        11,
        9,
        7,
        5,
        3,
        1,
        3,
        5,
        7,
        9,
        11,
        13,
        15,
        17,
        19,
        21,
        20,
        18,
        16,
        14,
        12,
        10,
        8,
        6,
        4,
        2,
        1,
        3,
        5,
        7,
        9,
        11,
        13,
        15,
        17,
        19,
        20,
        18,
        16,
        14,
        12,
        10,
        8,
        6,
        4,
        2,
        2,
        4,
        6,
        8,
        10,
        12,
        14,
        16,
        18,
        20,
        20,
        18,
        16,
        14,
        12,
        10,
        8,
        6,
        4,
        2 

        // 2,
        // 4,
        // 6,
        // 8,
        // 10,
        // 12,
        // 14,
        // 16,
        // 18,
        // 20,

        // 20,
        // 18,
        // 16,
        // 14,
        // 12,
        // 10,
        // 8,
        // 6,
        // 4,
        // 2,

        // 2,
        // 4,
        // 6,
        // 8,
        // 10,
        // 12,
        // 14,
        // 16,
        // 18,
        // 20,

        // 19,
        // 17,
        // 15,
        // 13,
        // 11,
        // 9,
        // 7,
        // 5,
        // 3,
        // 1,

        // 2,
        // 4,
        // 6,
        // 8,
        // 10,
        // 12,
        // 14,
        // 16,
        // 18,
        // 20,

        // 21,
        // 19,
        // 17,
        // 15,
        // 13,
        // 11,
        // 9,
        // 7,
        // 5,
        // 3,
        // 1,

        // 3,
        // 5,
        // 7,
        // 9,
        // 11,
        // 13,
        // 15,
        // 17,
        // 19,
        // 21,

        // 20,
        // 18,
        // 16,
        // 14,
        // 12,
        // 10,
        // 8,
        // 6,
        // 4,
        // 2,

        // 3,
        // 5,
        // 7,
        // 9,
        // 11,
        // 17,
        // 19,

        // 18,
        // 9,
        // 7,
        // 5,
        // 3

} ;
int taylorTopLongX[] = { 
    10,
    10,
    10,
    10,
    10,
    11,
    10,
    10,
    7,
    4,


    4,
    3,
    5,
    6,
    8,
    7,
    7,
    9, //10,      //column 8
    9, //10, 
    8, //9,
    8, //9,
    8,
    8,// 9,
    7,// 8,
    8,// 9,
    8,// 9,
    9,// 10,
    9,// 10,
    7,
    8,
    8,
    4,
    6,
    4,
    3,


    5,
    7,
    10,
    10,
    11,
    10,
    10,
    10,
    10,
    10
} ;


int taylorTopCropY[] = {

    3
    ,5
    ,7

    ,6
    ,4
    ,2

    ,3
    ,5
    ,7

    ,6
    ,4
    ,2

    ,3
    ,5
    ,7

    ,6
    ,4
    ,2

    ,3
    ,5
    ,7

    ,6
    ,4
    ,2

    ,3
    ,5
    ,7

    ,6
    ,4
    ,2

    ,3
    ,5
    ,7
    ,7
    ,5
    ,3
    ,3
    ,5
    ,7

    ,6
    ,4
    ,2

    ,2
    ,4
    ,6
    ,8

    ,7
    ,5
    ,3
    ,1

    ,1
    ,3
    ,5
    ,7

    ,7
    ,5
    ,3
    ,1

    ,1
    ,3
    ,5

    ,9
    ,7
    ,5
    ,3
    ,1

    ,2
    ,4
    ,6
    ,8

    ,9
    ,7
    ,5
    ,3
    ,1

    ,2
    ,4
    ,6
    ,8

    ,9
    ,7
    ,5
    ,3
    ,1

    ,2
    ,4
    ,6
    ,8

    ,9
    ,7
    ,5
    ,3
    ,1

    ,2
    ,4
    ,6
    ,8

    ,9
    ,7
    ,5
    ,3
    ,1

    ,2
    ,4
    ,6

    ,9
    ,7
    ,5
    ,3
    ,1

    ,2
    ,4
    ,6
    ,8

    ,7
    ,5
    ,3
    ,1

    ,2
    ,4
    ,6
    ,8

    ,7
    ,5
    ,3

    ,2
    ,4
    ,6
    ,8

    ,6       
    ,4       
    ,2       
          
    ,2       
    ,4       
    ,6       
           
    ,7     
    ,5       
    ,3       
           
    ,2       
    ,4       
    ,6       
          
    ,7       
    ,5       
    ,3       
           
    ,2       
    ,4       
    ,6       
          
    ,7     
    ,5       
    ,3       
        
    ,2       
    ,4       
    ,6       
           
    ,7       
    ,5       
    ,3       
           
    ,2       
    ,4       
    ,6   

    ,7       
    ,5       
    ,3
};

int taylorTopCropX [] = {
      3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,4
      ,4
      ,4
      ,4
      ,3
      ,5
      ,4
      ,5
      ,4
      ,5
      ,4
      ,5
      ,4
      ,5
      ,3
      ,5
      ,4
      ,4
      ,4
      ,3
      ,4
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
      ,3
};


int taylorSkirtX[] = {
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14
  } ;
int taylorSkirtY[] = { 



  } ;


int taylorCropSizeX = sizeof(taylorTopCropX)/sizeof(int);

int taylorCropSizeY = 9;


int taylorLongSizeX = sizeof(taylorTopLongX)/sizeof(int);

int taylorLongSizeY = 21;




int taylorSkirtSizeX = sizeof(taylorSkirtX)/sizeof(int);

int taylorSkirtSizeY = 14;

int forward(long frame, int i) {
  return i;
}

int backward(long frame, int i) {
  return totalLEDs - 1 - i;
}


int peak(long frame, int i) {

if(taylorMapTop == &pixToTaylorTopX){

  if (i < taylorLongSizeX / 2) {
    return i;
  } else { 
    return taylorLongSizeX - 1 - i;
  }
}
else if(taylorMapTop == &pixToTaylorTopY){
  if (i < taylorLongSizeY / 2) {
    return i;
  } else { 
    return taylorLongSizeY - 1 - i;
  }
}

else{

  if (i < totalLEDs / 2) {
    return i;
  } else { 
    return totalLEDs - 1 - i;
  }
}

}

int valley(long frame, int i) {

if(taylorMapTop == &pixToTaylorTopX){
  if (i < taylorLongSizeX / 2) {
    // return taylorLongSizeX / 2 - i;
    return taylorLongSizeX - i ;
  } else { 
    return i;
  }
}


else if(taylorMapTop == &pixToTaylorTopY){
  if (i <=  taylorLongSizeY / 2) {
    return  taylorLongSizeY / 2 - 8 - i ;
  } else { 
    return i- taylorLongSizeY;
  }
}

 else 
{
  if (i < totalLEDs / 2) {
    return totalLEDs / 2 - 1 - i;
  } else { 
    return i;
  }
}

}

int dither(long frame, int i) {
  if(taylorMapTop == &pixToTaylorTopX){
      if (i % 2 == 0) {
        return taylorCropSizeX - 1 - i;
      } else { 
        return i;
      }
}

else if(taylorMapTop == &pixToTaylorTopY){
 if (i % 2 == 0) {
        return taylorCropSizeY - 1 - i;
      } else { 
        return i;
      }
}

 else 
{
  if (i % 2 == 0) {
    return totalLEDs - 1 - i;
  } else { 
    return i;
  }
}
}



int peak_bottom(long frame, int i) {

if(taylorMapBottom == &pixToTaylorBotX){

  if (i < taylorSkirtSizeX / 2) {
    return i;
  } else { 
    return taylorSkirtSizeX - 1 - i;
  }
}
else if(taylorMapBottom == &pixToTaylorBotY){
  if (i < taylorSkirtSizeY / 2) {
    return i;
  } else { 
    return taylorSkirtSizeY - 1 - i;
  }
}

else{

  if (i < totalLEDs / 2) {
    return i;
  } else { 
    return totalLEDs - 1 - i;
  }
}

}

int valley_bottom(long frame, int i) {
 
if(taylorMapBottom == &pixToTaylorBotX){
  if (i < taylorSkirtSizeX / 2) {
    return taylorSkirtSizeX / 2 - i;
  } else { 
    return i + taylorSkirtSizeX/2 + 4;
  }
}

else if(taylorMapBottom == &pixToTaylorBotY){

  if (i < taylorSkirtSizeY / 2 ) {
    return taylorSkirtSizeY - i;
  } 
  else { 
    return i;
  }

}

 else 
{
  if (i < totalLEDs / 2) {
    return totalLEDs / 2 - 1 - i;
  } else { 
    return i;
  }
}

}

int dither_bottom(long frame, int i) {
  if(taylorMapBottom == &pixToTaylorBotX){
      if (i % 2 == 0) {
        return taylorSkirtSizeX - 1 - i;
      } else { 
        return i;
      }
}

else if(taylorMapBottom == &pixToTaylorBotY){
 if (i % 2 == 0) {
        return taylorSkirtSizeY - 1 - i;
      } else { 
        return i;
      }
}

 else 
{
  if (i % 2 == 0) {
    return totalLEDs - 1 - i;
  } else { 
    return i;
  }
}
}


//TODO maybe put this into an array to eliminate the need for a for loop
int pixToTaylorBotY(long frame, int p){

  int total = 0;
    for (int c = 0; c < 33; c++){
   total =  total + SKIRT_HEIGHT;
   if (total > p){
     if(c%2 == 0){
     total = total - p - 1;
     }
     else{
       total= SKIRT_HEIGHT - (total - p); 
       
     }
      return total;
   }
  }

}

int pixToTaylorBotX(long frame, int p){
  int index = 0;
  for(int i = 0; i < sizeof(taylorSkirtX); i++){

    if(p < index + taylorSkirtX[i]  && p > index - 1){
      return i;
    }
    index+=taylorSkirtX[i];
  }

}


int snake(long frame, int i) {
  return i; 
}


int pixToTaylorTopY(long frame, int p){
  // return taylorTopCropY[p];
  return taylorTopLongY[p];
}

int pixToTaylorTopX(long frame, int p){
  int index = 0;
  for(int i = 0; i < sizeof(taylorTopLongX); i++){

    if(p < index + taylorTopLongX[i]  && p > index - 1){
      return i;
    }
    index+=taylorTopLongX[i];
  }

}




// int pixToTaylorTopY(long frame, int p){
//   return taylorTopCropY[p];
// }

// int pixToTaylorTopX(long frame, int p){
//   int index = 0;
//   for(int i = 0; i < sizeof(taylorTopCropX); i++){

//     if(p < index + taylorTopCropX[i]  && p > index - 1){
//       return i;
//     }
//     index+=taylorTopCropX[i];
//   }

// }












