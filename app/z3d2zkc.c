#include <roki/rk_chain.h>

void z3d2zkcUsage(char *cmd)
{
  eprintf( "Usage: %s <.z3d file>\n", cmd );
  exit( EXIT_SUCCESS );
}

bool z3d2zkcConvert(zMShape3D *ms, char basename[])
{
  FILE *fp;
  register int i;

  if( !( fp = zOpenZTKFile( basename, "w" ) ) ){
    ZOPENERROR( basename );
    return false;
  }
  fprintf( fp, "[chain]\n" );
  fprintf( fp, "name: %s\n", basename );
  zMShape3DFPrint( fp, ms );
  fprintf( fp, "[link]\n" );
  fprintf( fp, "name: base\n" );
  fprintf( fp, "jointtype: fixed\n" );
  for( i=0; i<zMShape3DShapeNum(ms); i++ )
    fprintf( fp, "shape: %s\n", zName(zMShape3DShape(ms,i)) );
  fclose( fp );
  return true;
}

int main(int argc, char *argv[])
{
  zMShape3D ms;
  char basename[BUFSIZ];

  if( argc == 1 ) z3d2zkcUsage( argv[0] );
  if( !zMShape3DScanFile( &ms, argv[1] ) )
    return EXIT_FAILURE;
  zGetBasename( argv[1], basename, BUFSIZ );
  z3d2zkcConvert( &ms, basename );
  zMShape3DDestroy( &ms );
  return EXIT_SUCCESS;
}
