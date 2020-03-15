/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */

/**
 * Performs a multi-point flood fill using breadth x search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillBFS(FillerConfig &config)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill.
     */
     return fill<Queue>(config);
}

/**
 * Performs a multi-point flood fill using depth x search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillDFS(FillerConfig &config)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill.
     */
     return fill<Stack>(config);
}

/**
 * Run a multi-point flood fill on an image
 *
 * @param  config     FillerConfig struct with data for flood fill of image
 * @return animation  object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::fill(FillerConfig &config)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-x-search
     * fill, that structure is a Queue, for a depth-x-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure, and
     *              mark them as processed.
     *        2.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-x-search and
     *        depth-x-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** LEFT(-x), DOWN(+y), RIGHT(+x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must x try to fill the pixel to
     *        it's LEFT, then the one DOWN from it, then to the RIGHT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        Because we are doing a multi-point flood fill you will repeat the flood
     *        fill from several locations stored in the `centers` variable of FillerConfig
     *        struct. Initial fill points should be visited in the order they stored in the
     *        `centers` vector. If a pixel lies in the fill region of multiple start points,
     *        it should only be updated by the x fill. To repeat, pixels should only
     *        be modified the x time they are visited by the filler algorithm.
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you shouldto the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not t add a frame he number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     *
     */

    int count = 0;
    animation ani; 
    ani.addFrame(config.img); 
    OrderingStructure<center> os;
    set<int> visit;

    // for every center
    for(int i = 0; i < (int)config.pickers.size(); i++){
        int x = config.centers.at(i).x;
        int y = config.centers.at(i).y;

        // add the center into the os
        os.add(config.centers.at(i));
        count++;

        colorPicker *pick = config.pickers.at(i);

        // fill the center
        *config.img.getPixel(x,y) = pick->operator()(point(x,y,config.centers.at(i)));

        // mark the point as visited
        visit.insert(x*config.img.height()+y);

        // now deal with its neighbors
        while(!os.isEmpty()){
            center cen = os.remove();
    
            vector<point> neighbors;

            // left neighbor
            neighbors.push_back(point(cen.x-1, cen.y, config.centers.at(i)));

            // down neighbor
            neighbors.push_back(point(cen.x, cen.y+1, config.centers.at(i)));
            

            // right neighbor
            neighbors.push_back(point(cen.x+1, cen.y, config.centers.at(i)));

            // up neighbor
            neighbors.push_back(point(cen.x, cen.y-1, config.centers.at(i)));

            for(int j = 0; j < 4; j++){
                point c = neighbors[j];
                
                if(visit.count(c.x*config.img.height()+c.y) == 0){
                    // check if pixel is inside the bound of the image
                    if (   ((int)c.x >= 0)
                        && ((int)c.x < (int)config.img.width()) 
                        && ((int)c.y >= 0) 
                        && ((int)c.y < (int)config.img.height())
                        && (cen.color.dist(*config.img.getPixel(c.x, c.y)) <= config.tolerance)) {
                            
                        // add this neighbor the os as a new center
                        os.add(center(c.x, c.y, cen.color));
                        // fill this neighbor with pick
                        *config.img.getPixel(c.x, c.y) = pick->operator()(neighbors[j]);
                        // update count
                        count++;
                        visit.insert(c.x*config.img.height()+c.y);
                    }
                    if (count % config.frameFreq == 0){
                        ani.addFrame(config.img);
                    }
                }
            }
        }
    }
    ani.addFrame(config.img);
    return ani;
}
