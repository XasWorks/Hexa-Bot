module shine(angle=10, length=10, height=10, center=true) {
    if($children != 0) {
        intersection() {
            linear_extrude(height) {
                if(center) {
                    polygon([[0,0] , [length*cos(angle/2),length*sin(angle/2)] , [length,0] , [length*cos(-angle/2),length*sin(-angle/2)]]);
                }
                else {
                    polygon([[0,0] , [length*cos(angle),length*sin(angle)] ,  [length*cos(angle/2),length*sin(angle/2)] , [length,0]]);
                }
            } 
            children(); 
        }
    }   
    else {
        linear_extrude(height) {
            if(center) {
                polygon([[0,0] , [length*cos(angle/2),length*sin(angle/2)] , [length,0] , [length*cos(-angle/2),length*sin(-angle/2)]]);
            }
            else {
                polygon([[0,0] , [length*cos(angle),length*sin(angle)] ,  [length*cos(angle/2),length*sin(angle/2)] , [length,0]]);
            }
        }
    }  
}  

    
module cut(size=[10,10,10],translation=[0,0,0]) {
    intersection() {
        children();
        translate(translation) cube(size);
    }
}
