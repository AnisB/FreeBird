clear
heightMap = imread('heightmap.png');

W = size(heightMap,1);
L = size(heightMap,2);
normal = zeros(W,L,3);


for i=2:W-1
    i/(W-1)
    for j=2:L-1
        center = [ double(i) ;double(j) ;double(heightMap(i,j,1))];
        px = [ double(i+1); double(j) ;double(heightMap(i+1,j,1))];
        nx = [ double(i-1);double(j) ;double(heightMap(i-1,j,1))];
        py = [ double(i) ;double(j+1) ;double(heightMap(i,j+1,1))];
        ny = [ double(i) ;double(j-1) ;double(heightMap(i,j-1,1))];
        
        
        pxny = [ double(i+1); double(j-1) ;double(heightMap(i+1,j-1,1))];
        nxpy = [ double(i-1);double(j+1) ;double(heightMap(i-1,j+1,1))];
        pypx = [ double(i+1) ;double(j+1) ;double(heightMap(i+1,j+1,1))];
        nynx = [ double(i-1) ;double(j-1) ;double(heightMap(i-1,j-1,1))];
        
        V1 = center - px;
        V2 = center - nx;
        V3 = center - py;
        V4 = center - ny;
        
        
        V5 = center - pxny;
        V6 = center - nxpy;
        V7 = center - pypx;
        V8 = center - nynx;
        
        TG1 = cross(V1,[0 0 1]);
        TG2 = cross(V2,[0 0 1]);
        TG3 = cross(V3,[0 0 1]);
        TG4 = cross(V4,[0 0 1]);
        
        TG5 = cross(V5,[0 0 1]);
        TG6 = cross(V6,[0 0 1]);
        TG7 = cross(V7,[0 0 1]);
        TG8 = cross(V8,[0 0 1]);
        
        
        N1 = cross(TG1,V1);
        N2 = cross(TG2,V2);
        N3 = cross(TG3,V3);
        N4 = cross(TG4,V4);
        
        N5 = cross(TG5,V5);
        N6 = cross(TG6,V6);
        N7 = cross(TG7,V7);
        N8 = cross(TG8,V8);
            
        Nn1 = N1/norm(N1);
        Nn2 = N2/norm(N2);
        Nn3 = N3/norm(N3);
        Nn4 = N4/norm(N4);
        
        Nn5 = N5/norm(N5);
        Nn6 = N6/norm(N6);
        Nn7 = N7/norm(N7);
        Nn8 = N8/norm(N8);
        
        N = (Nn1 + Nn2 + Nn3 + Nn4 + 0.5*Nn5+ 0.5*Nn6 + 0.5*Nn7 + 0.5*Nn8)/6;
        normal(i,j,1) = N(1)/2 +0.5;
        normal(i,j,2) = N(2)/2 +0.5;
        normal(i,j,3) = N(3)/2 +0.5;
    end
end
size(normal)
K = image(W,L,normal);
imwrite(normal, 'normalMap.png');