clear
heightMap = imread('heightmap.png');
W = size(heightMap,1);
L = size(heightMap,2);
%W = 1000
%L = 1000
fid = fopen('palmiers.txt', 'wt');
for i=2:W-1
    i/(W-1)
    for j=2:L-1
       p = abs(randn(1));
       if heightMap(i,j) <= 20 
           p(1,1)
           if p(1,1)<0.0001
               istr =int2str(i);
               jstr =int2str(j);
               hstr =int2str(heightMap(i,j));
               fprintf(fid, istr);
               fprintf(fid, ' ');
               fprintf(fid, hstr);
               fprintf(fid, ' ');
               fprintf(fid, jstr);
               fprintf(fid, '\n');
           end
       end
    end
end

fid = fopen('maisons.txt', 'wt');
for i=2:W-1
    i/(W-1)
    for j=2:L-1
       p = abs(randn(1));
       if heightMap(i,j) >= 40 && heightMap(i,j) <= 120
           p(1,1)
           if p(1,1)<0.00001
               istr =int2str(i);
               jstr =int2str(j);
               hstr =int2str(heightMap(i,j));
               fprintf(fid, istr);
               fprintf(fid, ' ');
               fprintf(fid, hstr);
               fprintf(fid, ' ');
               fprintf(fid, jstr);
               fprintf(fid, '\n');
           end
       end
    end
end
fclose(fid);