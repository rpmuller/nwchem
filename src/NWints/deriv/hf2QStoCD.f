      Subroutine hf2QStoCD(dQ,dS,dC,dD,alpha,ipair,ff,NPP,NPQ,Nint,
     &       ictrc,ictrd)
c $Id: hf2QStoCD.f,v 1.3 1994-06-07 00:31:17 d3e129 Exp $

      Implicit real*8 (a-h,o-z)
      Implicit integer (i-n)
      integer ictrc,ictrd

c--> Derivative Integrals WRT (Q,S)

      Dimension dQ((NPQ*NPP),Nint),dS((NPQ*NPP),Nint)

c--> Derivative Integrals WRT (C,D)

      Dimension dC(Nint),dD(Nint)

c--> Exponents & Pair Index

      Dimension alpha(2,NPP),ipair(2,NPP)

c--> Scratch space

      Dimension ff(2,(NPQ*NPP))
c
c Transform derivative integrals wrt (Q,S) to (C,D).
c
c N.B. It is assumed that the product of contraction coefficients has been
c      factored into each primitive (Q,S) integral derivative. Thus, this 
c      routine currently transforms primitive (Q,S) integral derivatives to 
c      contracted (C,D) integral derivatives.
c
c*******************************************************************************

c Initialize derivative integrals wrt to (C,D).

      do 10 nn = 1,Nint
       dC(nn) = 0.D0
       dD(nn) = 0.D0
   10 continue

      if (ictrc.eq.ictrd) then
        do 00100 nn = 1,Nint
          do 00200 mr = 1,(NPQ*NPP)
            dC(nn) = dC(nn) + dQ(mr,nn)
00200     continue
00100   continue
      else
c Compute exponent ratios.

        do 15 mq = 1,NPQ
          ff(1,mq) = alpha(1,mq)/(alpha(1,mq) + alpha(2,mq))
          ff(2,mq) = alpha(2,mq)/(alpha(1,mq) + alpha(2,mq))
15      continue
        
        mr = NPQ
        do 25 mp = 2,NPP
          do 20 mq = 1,NPQ
            mr = mr + 1
            
            ff(1,mr) = ff(1,mq)
            ff(2,mr) = ff(2,mq)
            
20        continue
25      continue
        
c Transform.
        
        do 40 nn = 1,Nint
          
          do 30 mr = 1,(NPQ*NPP)
            dC(nn) = dC(nn) + (ff(1,mr)*dQ(mr,nn) + dS(mr,nn))
            dD(nn) = dD(nn) + (ff(2,mr)*dQ(mr,nn) - dS(mr,nn))
30        continue
          
40      continue
        
      endif
      end
