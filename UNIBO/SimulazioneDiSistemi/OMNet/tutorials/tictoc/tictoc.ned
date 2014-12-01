
simple Txc1
{
  gates:
    input in;
    output out;
}


network Tictoc1
{
  submodules:
    tic: Txc1;
    toc: Txc1;
  connections:
    tic.out --> { delay = 100ms; } --> toc.in;
    tic.in <-- { delay = 100ms; } <-- toc.out;
}
