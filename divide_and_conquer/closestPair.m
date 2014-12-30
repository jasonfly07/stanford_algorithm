% Search the closest pair of points. 
function closestPair()
numPts = 2500;
pts = rand(numPts,2)*10000;

scatter(pts(:,1),pts(:,2));
hold on;

tic
minPair1 = closestPair1(pts);
toc
tic
minPair2 = closestPair2(pts);
toc
scatter(minPair2(:,1),minPair2(:,2),'rx');

end

% 1. Brute force approach. O(n^2).
function minPair = closestPair1(pts)
minDist = intmax;
numPts = size(pts,1);
for i=1:numPts
    for j=i+1:numPts
        currDist = norm(pts(i,:)-pts(j,:));
        if currDist<minDist
            minDist = currDist;
            minPairInd = [i,j];
        end
    end
end
minPair = pts(minPairInd,:);
end

% 2. Divide & Conquer approach. O(nlogn).
function minPair = closestPair2(pts)
% Base case
% If there's only one point, there's no min pair. 
if size(pts,1)==1
    minPair = [];
    return;
end

% Recursive case
sortedX = sortrows(pts,1);
sortedY = sortrows(pts,2);

sizePts = size(pts,1);
% Divide pts into Q(left) and R(right).
Q = sortedX(1: floor(sizePts/2), :);
R = sortedX(floor(sizePts/2)+1: sizePts, :);
minPairQ = closestPair2(Q);
minPairR = closestPair2(R);

% Due to the design of this recursive function
% only one of them will be intmax
if isempty(minPairQ)
    minDistQ = intmax;
else
    minDistQ = norm(minPairQ(1,:)-minPairQ(2,:));
end

if isempty(minPairR)
    minDistR = intmax;
else
    minDistR = norm(minPairR(1,:)-minPairR(2,:));
end

% delta is the minimum distance from Q and R.
% It'd be used as the interval for the split strip.
if minDistQ < minDistR
    delta = minDistQ;
    currBestPair = minPairQ;
else
    delta = minDistR;
    currBestPair = minPairR;
end

% x_bar is the center x of the strip.
% Sy contains all the points in the strip, sorted in y-coordinate.
x_bar = Q(end,1);
Sy = sortedY( sortedY(:,1)>=x_bar-delta & sortedY(:,1)<=x_bar+delta, :);
currBestDist = delta;

% Copied the way this double for-loop is constructed
% from the video. Looks very short and elegant.
for i=1:size(Sy,1)-1
    for j=1:min([7, size(Sy,1)-i])
        pt1 = Sy(i,:);
        pt2 = Sy(i+j,:);
        splitDist = norm(pt1-pt2);
        if splitDist<currBestDist
            currBestDist = splitDist;
            currBestPair = [pt1;pt2];
        end
    end
end

minPair = currBestPair;

end

