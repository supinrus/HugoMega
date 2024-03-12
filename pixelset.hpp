void set_pixel(SDL_Surface *surface, Uint32 x, Uint32 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + y * surface->pitch
                                             + x * surface->format->BytesPerPixel);
  Uint8 a_old;
  Uint32 tmp,rgb_old,rgb = b+g*256+r*256*256;
  rgb_old = *target_pixel%(256*256*256);
  a_old = *target_pixel/(256*256*256);
  tmp = rgb*a+rgb_old*(255-a);
  rgb_old = tmp/255;
  tmp = a*255+a_old*(255-a);
  a_old = tmp/255;
  *target_pixel = rgb_old+a_old*256*256*256;
}

/*void DownColorSurface(SDL_Surface *surf, Uint32 down, Uint32 w, Uint32 h)
{
  Uint32 i,j;
  Uint32 *tp;
  Uint32 tmp;
  Uint8 r,g,b,a;
  for (i = 0; i<w; ++i)
    for (j = 0; j<h; ++j)
    {
      tp = (Uint32 *) ((Uint8 *) surf->pixels
                                             + j * surf->pitch
                                             + i * surf->format->BytesPerPixel);
      tmp = *tp;
      b = tmp%256;
      tmp = tmp/256;
      g = tmp%256;
      tmp = tmp/256;
      r = tmp%256;
      tmp = tmp/256;
      a = tmp%256;
      b = b/down;
      g = g/down;
      r = r/down;
      tmp = b+g*256+r*256*256+a*256*256*256;
      *tp = tmp;
    }
}

void MyBlitSurface(SDL_Surface *src, SDL_Surface *dst, Uint32 w, Uint32 h)
{
  Uint32 i,j,rgb1,rgb2,tmp;
  Uint8 a1,a2;
  Uint32 *tp1,*tp2;
  for (i = 0; i<w; ++i)
    for (j = 0; j<h; ++j)
      {
        tp1 = (Uint32 *) ((Uint8 *) src->pixels
                                             + j * src->pitch
                                             + i * src->format->BytesPerPixel);
        tp2 = (Uint32 *) ((Uint8 *) dst->pixels
                                             + j * dst->pitch
                                             + i * dst->format->BytesPerPixel);
        rgb1 = *tp1%(256*256*256);
        rgb2 = *tp2%(256*256*256);
        a1 = *tp1/(256*256*256);
        a2 = *tp2/(256*256*256);
        tmp = rgb1*a1+rgb2*(255-a1);
        rgb2 = tmp/255;
        tmp = a1*255+a2*(255-a1);
        a2 = a2/255;
        *tp2 = rgb2+a2*256*256*256;
      }
}

void ClearSurface(SDL_Surface *surf, Uint32 w, Uint32 h)
{
  Uint32 i,j;
  Uint32 *tp;
  for (i = 0; i<w; ++i)
    for (j = 0; j<h; ++j)
    {
      tp = (Uint32 *) ((Uint8 *) surf->pixels
                                             + j * surf->pitch
                                             + i * surf->format->BytesPerPixel);
      *tp = 0;
    }
} */